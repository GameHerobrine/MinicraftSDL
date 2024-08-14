#include <crafting/crafting.h>
#include <gfx/spritesheet.h>
#include <gfx/font.h>
#include <SDL/SDL.h>
#include <game.h>
#include <inputhandler.h>
#include <utils/arraylist.h>
#include <utils/utils.h>
#include <screen/menu.h>
#include <level/tile/tile.h>
#include <item/resource/resource.h>
#include <level/level.h>
#include <gfx/color.h>
#ifndef NSPIRE
#include <linux/limits.h>
#endif
#include <entity/player.h>
#include <item/item.h>
#include <icons.h>

#ifdef NSPIRE
#include <os.h>
#endif

Screen game_screen;
Screen game_lightScreen;

int g_ticks = 0; //perf measure
int g_frames = 0; //perf measure

unsigned long tickCount = 0;

SDL_Color sdl_colors[256];

enum menu_id current_menu;
char game_hasfocus = 0;
int game_pendingLevelChange = 0;
char updatePerfctr = 0;
char running = 1;
char isingame = 0;

void game_set_menu(enum menu_id menu){
	current_menu = menu;
	init_menu(menu);
}

int game_playerDeadTime = 0;
int game_wonTimer = 0;
int game_gameTime = 0;
char game_hasWon = 0;
Level game_levels[5] = {0};
int game_currentLevel;
Level* game_level;

Player* game_player = 0;

void game_changeLevel(int dir){
	level_removeEntity1(game_level, game_player);
	game_currentLevel += dir;
	game_level = game_levels + game_currentLevel;
	game_player->mob.entity.x = (game_player->mob.entity.x >> 4) * 16 + 8;
	game_player->mob.entity.y = (game_player->mob.entity.y >> 4) * 16 + 8;
	level_addEntity(game_level, game_player);
}
void game_won(){
	game_wonTimer = 60*3;
	game_hasWon = 1;
}
void game_reset(){
	game_playerDeadTime = 0;
	game_wonTimer = 0;
	game_gameTime = 0;
	game_hasWon = 0;

	for(int i = 0; i < 5; ++i){
		printf("Freeing level %d\n", i);
		level_free(game_levels + i);
	}
	if(!isingame) return;
	memset(game_levels, 0, sizeof(game_levels));
	game_currentLevel = 3;
	level_init(game_levels + 4, 128, 128, 1, 0);
	level_init(game_levels + 3, 128, 128, 0, game_levels + 4);
	level_init(game_levels + 2, 128, 128, -1, game_levels + 3);
	level_init(game_levels + 1, 128, 128, -2, game_levels + 2);
	level_init(game_levels + 0, 128, 128, -3, game_levels + 1);
	if(game_player) {
		call_entity_free(game_player);
		free(game_player);
	}
	game_level = game_levels + game_currentLevel;
	game_player = (Player*) malloc(sizeof(Player));
	player_create(game_player);
	player_findStartPos(game_player, game_level);

	level_addEntity(game_level, game_player);

	for(int i = 0; i < 5; ++i) level_trySpawn(game_levels + i, 5000);
}

void game_init(){
	levelgen_preinit();
	font_pre_init();
	init_resources();
	init_tiles();
	init_menus();
	crafting_init();

	int pp = 0;
	for(int r = 0; r < 6; ++r){
		for(int g = 0; g < 6; ++g){
			for(int b = 0; b < 6; ++b){
				int rr = r*255 / 5;
				int gg = g*255 / 5;
				int bb = b*255 / 5;
				int mid = (rr * 30 + gg * 59 + bb * 11) / 100;
				
				int r1 = ((rr + mid * 1) / 2) * 230 / 255 + 10;
				int g1 = ((gg + mid * 1) / 2) * 230 / 255 + 10;
				int b1 = ((bb + mid * 1) / 2) * 230 / 255 + 10;

				sdl_colors[pp].r = r1;
				sdl_colors[pp].g = g1;
				sdl_colors[pp].b = b1;
				++pp;
			}
		}
	}
	
	create_screen(&game_screen, WIDTH, HEIGHT, &icons_spritesheet);
	create_screen(&game_lightScreen, WIDTH, HEIGHT, &icons_spritesheet);
	
	game_reset();
	game_set_menu(mid_TITLE);
}

void set_pixel(SDL_Surface* surface, int x, int y, int color){
	*(int*)(surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel) = color;
}
char teststr[] = "test uwu";

void game_tick(){
	++tickCount;
	if(!game_hasfocus){
		//TODO release all keys
	}else{
		if(isingame) if(!game_player->mob.entity.removed && !game_hasWon) ++game_gameTime;
		input_tick();

		if(current_menu){
			tick_menu(current_menu);
		}else{
			if(game_player->mob.entity.removed){
				++game_playerDeadTime;
				if(game_playerDeadTime > 60){
					game_set_menu(mid_DEAD);
				}
			}else{
				if(game_pendingLevelChange != 0){
					game_set_menu(mid_LEVEL_TRANSITION);
					game_pendingLevelChange = 0;
				}
			}

			if(game_wonTimer > 0){
				if(--game_wonTimer == 0){
					game_set_menu(mid_WON);
				}
			}

			level_tick(game_level);
			++tile_tickCount;
		}
	}
}

void game_renderGui(){

#ifdef TEST_SHOWPORTALPOS
	if(isingame){
		char hax[64];
		int x = game_player->mob.entity.x >> 4;
		int y = game_player->mob.entity.y >> 4;
		sprintf(hax, "P %d %d\00", x, y);
		font_draw(hax, strlen(hax), &game_screen, 2, 2, getColor4(000, 200, 500, 533));
		int Scnt = 10;

		for(x = 0; x < game_player->mob.entity.level->w; ++x){
			for(y = 0; y < game_player->mob.entity.level->h; ++y){
				if(level_get_tile(game_player->mob.entity.level, x, y) == STAIRS_UP){
					sprintf(hax, "U %d %d\00", x, y);
					font_draw(hax, strlen(hax), &game_screen, 2, Scnt, getColor4(000, 200, 500, 533));
					Scnt += 8;
				}

				if(level_get_tile(game_player->mob.entity.level, x, y) == STAIRS_DOWN){
					sprintf(hax, "D %d %d\00", x, y);
					font_draw(hax, strlen(hax), &game_screen, 2, Scnt, getColor4(000, 200, 500, 533));
					Scnt += 8;
				}
			}
		}

		if(game_player->mob.entity.level->depth == 1){
			for(int i = 0; i < game_player->mob.entity.level->entities.size; ++i){
				Entity* e = game_player->mob.entity.level->entities.elements[i];
				if(e->type == AIRWIZARD){
					sprintf(hax, "W %d %d\00", e->x>> 4, e->y>> 4);
					font_draw(hax, strlen(hax), &game_screen, 2, Scnt, getColor4(000, 200, 500, 533));
					Scnt += 8;
					break;
				}
			}
		}
	}
#endif

#ifdef FPS_AND_TICKS
	char fpsticks[64];

	sprintf(fpsticks, "%dfps %dticks\00", g_frames, g_ticks);
	font_draw(fpsticks, strlen(fpsticks), &game_screen, 2, 2, getColor4(000, 200, 500, 533));
#endif

	for(int y = 0; y < 2; ++y){
		for(int x = 0; x < 20; ++x){
			render_screen(&game_screen, x*8, game_screen.h - 16 + y*8, 0 + 12 * 32, getColor4(0, 0, 0, 0), 0);
		}
	}
	if(isingame){
		for(int i = 0; i < 10; ++i){
			if(i < game_player->mob.health){
				render_screen(&game_screen, i * 8, game_screen.h - 16, 0 + 12 * 32, getColor4(000, 200, 500, 533), 0);
			}else{
				render_screen(&game_screen, i * 8, game_screen.h - 16, 0 + 12 * 32, getColor4(000, 100, 000, 000), 0);
			}

			if(game_player->staminaRechargeDelay > 0){
				if(game_player->staminaRechargeDelay / 4 % 2 == 0){
					render_screen(&game_screen, i * 8, game_screen.h - 8, 1 + 12 * 32, getColor4(000, 555, 000, 000), 0);
				}else{
					render_screen(&game_screen, i * 8, game_screen.h - 8, 1 + 12 * 32, getColor4(000, 110, 000, 000), 0);
				}
			}else{
				if(i < game_player->stamina){
					render_screen(&game_screen, i * 8, game_screen.h - 8, 1 + 12 * 32, getColor4(000, 220, 550, 553), 0);
				}else{
					render_screen(&game_screen, i * 8, game_screen.h - 8, 1 + 12 * 32, getColor4(000, 110, 000, 000), 0);
				}
			}
		}

		if(game_player->activeItem){
			item_renderInventory(game_player->activeItem, &game_screen, 10*8, game_screen.h - 16);
		}
	}
	if(current_menu){
		render_menu(current_menu, &game_screen);
	}
}

char click_to_focus[] = "Click to focus!";
void game_renderFocusNagger(){
	//click_to_focus
	int c2fLen = strlen(click_to_focus);
	int xx = (WIDTH - c2fLen * 8) / 2;
	int yy = (HEIGHT - 8) / 2;
	
	int w = c2fLen;
	int h = 1;
	
	render_screen(&game_screen, xx - 8, yy - 8, 0 + 13 * 32, getColor4(-1, 1, 5, 445), 0);
	render_screen(&game_screen, xx + w * 8, yy - 8, 0 + 13 * 32, getColor4(-1, 1, 5, 445), 1);
	render_screen(&game_screen, xx - 8, yy + 8, 0 + 13 * 32, getColor4(-1, 1, 5, 445), 2);
	render_screen(&game_screen, xx + w * 8, yy + 8, 0 + 13 * 32, getColor4(-1, 1, 5, 445), 3);
	
	for(int x = 0; x < w; ++x){
		render_screen(&game_screen, xx + x * 8, yy - 8, 1 + 13 * 32, getColor4(-1, 1, 5, 445), 0);
		render_screen(&game_screen, xx + x * 8, yy + 8, 1 + 13 * 32, getColor4(-1, 1, 5, 445), 2);
	}
	
	for(int y = 0; y < h; ++y){
		render_screen(&game_screen, xx - 8, yy + y * 8, 2 + 13 * 32, getColor4(-1, 1, 5, 445), 0);
		render_screen(&game_screen, xx + w * 8, yy + y * 8, 2 + 13 * 32, getColor4(-1, 1, 5, 445), 1);
	}
	
	if((tickCount / 20) % 2 == 0){
		font_draw(click_to_focus, c2fLen, &game_screen, xx, yy, getColor4(5, 333, 333, 333));
	}else{
		font_draw(click_to_focus, c2fLen, &game_screen, xx, yy, getColor4(5, 555, 555, 555));
	}
}

void game_render(){
	if(isingame){
		int xScroll = game_player->mob.entity.x - game_screen.w / 2;
		int yScroll = game_player->mob.entity.y - (game_screen.h - 8) / 2;

		if (xScroll < 16) xScroll = 16;
		if (yScroll < 16) yScroll = 16;
		if (xScroll > game_level->w * 16 - game_screen.w - 16) xScroll = game_level->w * 16 - game_screen.w - 16;
		if (yScroll > game_level->h * 16 - game_screen.h - 16) yScroll = game_level->h * 16 - game_screen.h - 16;

		if(game_currentLevel > 3){
			int col = getColor4(20, 20, 121, 121);

			for(int y = 0; y < 14; ++y){
				for(int x = 0; x < 24; ++x){
					render_screen(&game_screen, x * 8 - ((xScroll / 4) & 7), y * 8 - ((yScroll / 4) & 7), 0, col, 0);
				}
			}
		}

		level_renderBackground(game_level, &game_screen, xScroll, yScroll);
		level_renderSprites(game_level, &game_screen, xScroll, yScroll);

		if(game_currentLevel < 3){
			clear_screen(&game_lightScreen, 0);
			renderLight(game_level, &game_lightScreen, xScroll, yScroll);
			screen_overlay(&game_screen, &game_lightScreen, xScroll, yScroll);
		}
	}
	
	game_renderGui();
	if(!game_hasfocus){
		game_renderFocusNagger();
	}
}

int main(int argc, char** argv){
	unsigned long long int lastTime = getTimeUS();
	unsigned long long int lastPrinted = lastTime;
	double unprocessed = 0;
#ifdef NSPIRE
	const double usPerTick = (32000.0 / 60); //1ms = 32
#else
	const double usPerTick = 1000000.0 / 60;
#endif

#ifdef LIMITFPS
	unsigned long long int nextExceptedFrameRenderTime = 0;
#endif
	unsigned long long int now  = 0;
	int ticks = 0, frames = 0;

	unsigned char* prevBuf = 0;
	int ret = 0;
	int winHeight = HEIGHT*SCALE;
	int winWidth = WIDTH*SCALE;
	char needsFlip = 0;
	int flipXMin = 0, flipXMax = 0, flipYMin = 0, flipYMax = 0;
	printf("Starting...\n");

	SDL_Surface* surface;
	SDL_Event event;
	SDL_KeyboardEvent* keyEvent = &event; 
	SDL_Rect pixel = {0, 0, SCALE, SCALE};
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current working dir: %s\n", cwd);
	}
	game_init();
	
	SDL_Init(SDL_INIT_VIDEO);
#ifndef NSPIRE
	SDL_WM_SetCaption("Minicraft", 0);
#endif
	surface = SDL_SetVideoMode(winWidth, winHeight, 8, SDL_SWSURFACE); //SDL_HWPALETTE|SDL_DOUBLEBUF);
	
	if(surface == 0){
		printf("Failed to set videomode\n");
		ret = 1;
		goto QUIT;
	}

	SDL_SetPalette(surface, SDL_LOGPAL|SDL_PHYSPAL, sdl_colors, 0, 256);
#ifdef LEVELGENTEST
#define set_px(x, y, color) {\
	pixel.x = x*SCALE;\
	pixel.y = y*SCALE;\
	SDL_FillRect(surface, &pixel, color);\
}	
	
	int w = 128;
	int h = 128;
	unsigned char* map;
	unsigned char* data;
	pixel.w = SCALE;
	pixel.h = SCALE;
	createAndValidateSkyMap(&map, &data, w, h, 3);
	printf("gen stopped\n");
	surface = SDL_SetVideoMode(w*SCALE, h*SCALE, 32, SDL_HWPALETTE|SDL_DOUBLEBUF);
	for(int y = 0; y < h; ++y){
		for(int x = 0; x < w; ++x){
			int i = x + y * w;
			
			if(map[i] == WATER) set_px(x, y, 0x000080);
			if(map[i] == GRASS) set_px(x, y, 0x208020);
			if(map[i] == ROCK) set_px(x, y, 0xa0a0a0);
			if(map[i] == DIRT) set_px(x, y, 0x604040);
			if(map[i] == SAND) set_px(x, y, 0xa0a040);
			if(map[i] == TREE) set_px(x, y, 0x003000);
			if(map[i] == LAVA) set_px(x, y, 0xff2020);
			if(map[i] == CLOUD) set_px(x, y, 0xa0a0a0);
			if(map[i] == STAIRS_DOWN) set_px(x, y, 0xffffff);
			if(map[i] == STAIRS_UP) set_px(x, y, 0xffffff);
			if(map[i] == CLOUD_CACTUS) set_px(x, y, 0xff00ff);
		}
	}
	SDL_Flip(surface);
	while(running)
	{
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = 0;
					break;
			}
		}
	}
	free(map);
	free(data);
	goto QUIT;
#endif

	prevBuf = malloc(game_screen.h*game_screen.w);
	for(int i = 0; i < game_screen.h*game_screen.w; ++i) prevBuf[i] = 0;
	game_hasfocus = 1;

#ifdef NSPIRE
	const unsigned timer_load_value = 0xffffffff;
	//no classic support =<
	volatile unsigned *load = (unsigned*)0x900D0020;
	volatile unsigned *read = (unsigned*)0x900D0024;
	volatile unsigned *control = (unsigned*)0x900D0028;
	volatile unsigned *int_clear = (unsigned*)0x900D002C;
	volatile unsigned *int_status = (unsigned*)0x900D0030;

	unsigned orig_control = *control;
	unsigned orig_load = *load;


	*control = 0;
	*int_clear = 1;
	*load = timer_load_value;
	*control = 0b11100011;

	unprocessed = 0;
	now = 0;
#endif


	while(running)
	{
#ifndef NSPIRE
		now = getTimeUS();

		unprocessed += (now - lastTime) / usPerTick;
#else
		unsigned passed = timer_load_value - *read;
		now += passed;

		*control = 0;
		*int_clear = 1;
		*load = timer_load_value;
		*control = 0b11100011;

		unprocessed += (float)passed / usPerTick;
#endif

		while(unprocessed >= 1){
			++ticks;
			game_tick();
			--unprocessed;
		}
		
		while(SDL_PollEvent(&event))
		{
			switch(event.type){
				case SDL_KEYUP:
					//printf("key up %d\n", keyEvent->keysym.sym);
					input_toggle(keyEvent->keysym.sym, 0);
					break;
				case SDL_KEYDOWN:
					//printf("key down %d\n", keyEvent->keysym.sym);
					input_toggle(keyEvent->keysym.sym, 1);
					break;
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_ACTIVEEVENT:
#ifndef NSPIRE
					game_hasfocus = event.active.state != 2; //TODO better focus detection
#else
					game_hasfocus = 1;
#endif
					break;
			}
		}
		needsFlip = 0;
		flipXMin = winWidth;
		flipXMax = 0;
		flipYMin = winHeight;
		flipYMax = 0;
#ifdef LIMITFPS

		if(now < nextExceptedFrameRenderTime){
			goto SKIP_RENDER;
		}else{
#ifdef NSPIRE
			nextExceptedFrameRenderTime = now + 32000/LIMITFPS;
#else
			nextExceptedFrameRenderTime = now + 1000000/LIMITFPS;
#endif
		}
#endif

		++frames;
		game_render();

		for(int y = 0; y < game_screen.h; ++y){
			pixel.y = y*SCALE;
			for(int x = 0; x < game_screen.w; ++x){
				pixel.x = x*SCALE;
				int index = y * game_screen.w + x;
				int screen_px = game_screen.pixels[index];
				if(screen_px != prevBuf[index]){
					prevBuf[index] = screen_px;
					needsFlip = 1;
					int xmin = pixel.x;
					int xmax = xmin + SCALE;
					int ymin = pixel.y;
					int ymax = ymin + SCALE;
					if(xmin < flipXMin) flipXMin = xmin;
					if(xmax > flipXMax) flipXMax = xmax;
					if(ymin < flipYMin) flipYMin = ymin;
					if(ymax > flipYMax) flipYMax = ymax;

#if SCALE == 1
					*(unsigned char*)(surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel) = screen_px;
#elif SCALE == 2
					*(unsigned char*)(surface->pixels + (y*SCALE) * surface->pitch + (x*SCALE) * surface->format->BytesPerPixel) = screen_px;
					*(unsigned char*)(surface->pixels + (y*SCALE) * surface->pitch + (x*SCALE+1) * surface->format->BytesPerPixel) = screen_px;
					*(unsigned char*)(surface->pixels + (y*SCALE+1) * surface->pitch + (x*SCALE) * surface->format->BytesPerPixel) = screen_px;
					*(unsigned char*)(surface->pixels + (y*SCALE+1) * surface->pitch + (x*SCALE+1) * surface->format->BytesPerPixel) = screen_px;
#else
					SDL_FillRect(surface, &pixel, screen_px);
#endif
				}

			}
		}

		SKIP_RENDER:
#ifdef NSPIRE
		if(nsp_exit.down && current_menu == mid_TITLE){
			running = 0;
			continue;
		}
#endif
		if(needsFlip) {
			printf("RENDERING %d %d %d %d\n", flipXMin, flipXMax, flipYMin, flipYMax);
			SDL_UpdateRect(surface, flipXMin, flipYMin, flipXMax-flipXMin, flipYMax-flipYMin);
		}

#ifdef NSPIRE
	#define PRNT_DELAY 32*1000
#else
	#define PRNT_DELAY 1000000
#endif
		if(now - lastPrinted > PRNT_DELAY){
			printf("%d ticks, %d fps\n", ticks, frames);
			g_ticks = ticks;
			g_frames = frames;
			ticks = 0;
			frames = 0;
			updatePerfctr = 1;
			lastPrinted = now;
		}
		lastTime = now; //not like in java
	}
	QUIT:

#ifdef NSPIRE
	*control = 0; // disable timer
	*int_clear = 1; // clear interrupt status
	*control = orig_control & 0b01111111; // timer still disabled
	*load = orig_load;
	*control = orig_control;
#endif

	if(prevBuf) free(prevBuf);
	// Quit SDL
	SDL_Quit();
	crafting_free();
	delete_screen(&game_screen);
	delete_screen(&game_lightScreen);

	for(int i = 0; i < 5; ++i){
		printf("Freeing level %d\n", i);
		level_free(game_levels + i);
	}

	if(game_player) {
		call_entity_free(game_player);
		free(game_player);
	}
	return ret;
}
