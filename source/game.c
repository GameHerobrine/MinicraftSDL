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
#include <linux/limits.h>
#include <entity/player.h>

SpriteSheet icons_spritesheet;
Screen game_screen;
Screen game_lightScreen;

unsigned long tickCount = 0;

int game_colors[256];

enum menu_id current_menu;
char game_hasfocus = 0;


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

void game_reset(){
	game_playerDeadTime = 0;
	game_wonTimer = 0;
	game_gameTime = 0;
	game_hasWon = 0;

	for(int i = 0; i < 5; ++i){
		printf("Freeing level %d\n", i);
		level_free(game_levels + i);
	}
	
	memset(game_levels, 0, sizeof(game_levels));
	game_currentLevel = 3;
	level_init(game_levels + 4, 128, 128, 1, 0);
	level_init(game_levels + 3, 128, 128, 0, game_levels + 4);
	level_init(game_levels + 2, 128, 128, -1, game_levels + 3);
	level_init(game_levels + 1, 128, 128, -2, game_levels + 2);
	level_init(game_levels + 0, 128, 128, -3, game_levels + 1);
	
	game_level = game_levels + game_currentLevel;
	game_player = (Player*) malloc(sizeof(Player));
	player_create(game_player);
	player_findStartPos(game_player, game_level);

	level_addEntity(game_level, game_player);

	//TODO 5 times: levels.trySpawn(5000);
}

void game_init(){
	levelgen_preinit();
	font_pre_init();
	init_resources();
	init_tiles();
	init_menus();
	
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
				game_colors[pp++] = r1 << 16 | g1 << 8 | b1;
			}
		}
	}
	
	
	FILE* f = fopen("icons.rimg", "rb");
	if(!f){
		printf("Failed to open icons!\n");
		return;
	}
	create_spritesheet(&icons_spritesheet, f, 256, 256);
	fclose(f);
	
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
		//TODO if (!player.removed && !hasWon) gameTime++;
		input_tick();

		if(current_menu){
			tick_menu(current_menu);
		}else{
			//TODO tick player

			level_tick(game_level);
			++tile_tickCount;
		}
	}
}

void game_renderGui(){
	for(int y = 0; y < 2; ++y){
		for(int x = 0; x < 20; ++x){
			render_screen(&game_screen, x*8, game_screen.h - 16 + y*8, 0 + 12 * 32, getColor4(0, 0, 0, 0), 0);
		}
	}
	
	/*TODO
	 for (int i = 0; i < 10; i++) {
			if (i < player.health)
				screen.render(i * 8, screen.h - 16, 0 + 12 * 32, Color.get(000, 200, 500, 533), 0);
			else
				screen.render(i * 8, screen.h - 16, 0 + 12 * 32, Color.get(000, 100, 000, 000), 0);

			if (player.staminaRechargeDelay > 0) {
				if (player.staminaRechargeDelay / 4 % 2 == 0)
					screen.render(i * 8, screen.h - 8, 1 + 12 * 32, Color.get(000, 555, 000, 000), 0);
				else
					screen.render(i * 8, screen.h - 8, 1 + 12 * 32, Color.get(000, 110, 000, 000), 0);
			} else {
				if (i < player.stamina)
					screen.render(i * 8, screen.h - 8, 1 + 12 * 32, Color.get(000, 220, 550, 553), 0);
				else
					screen.render(i * 8, screen.h - 8, 1 + 12 * 32, Color.get(000, 110, 000, 000), 0);
			}
		}
		if (player.activeItem != null) {
			player.activeItem.renderInventory(screen, 10 * 8, screen.h - 16);
		}
	 */
	
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
	//int xScroll = 1688, yScroll = 1168;
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
	
	
	game_renderGui();
	if(!game_hasfocus){
		game_renderFocusNagger();
	}
}

int main(int argc, char** argv){
	unsigned long long int lastTime = getTimeUS();
	unsigned long long int lastPrinted = lastTime;
	double unprocessed = 0;
	const double usPerTick = 1000000.0 / 60;
	unsigned long long int now  = 0;
	unsigned long long int ticks = 0; //perf measure
	unsigned long long int frames = 0; //perf measure
	
	int ret = 0;
	int winHeight = HEIGHT*SCALE;
	int winWidth = WIDTH*SCALE;
	char running = 1;
	
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
	SDL_WM_SetCaption("Minicraft", 0);
	surface = SDL_SetVideoMode(winWidth, winHeight, 32, SDL_HWPALETTE|SDL_DOUBLEBUF);
	
	if(surface == 0){
		printf("Failed to set videomode\n");
		ret = 1;
		goto QUIT;
	}

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
	
	
	while(running)
	{
		now = getTimeUS();
		unprocessed += (now - lastTime) / usPerTick;
		//lastTime = now;
		
		while(unprocessed >= 1){
			++ticks;
			game_tick();
			--unprocessed;
		}
		
		while(SDL_PollEvent(&event))
		{
			//printf("%d\n", event.type);
			
			switch(event.type){
				case SDL_KEYUP:
					printf("key up %d\n", keyEvent->keysym.sym);
					input_toggle(keyEvent->keysym.sym, 0);
					break;
				case SDL_KEYDOWN:
					printf("key down %d\n", keyEvent->keysym.sym);
					input_toggle(keyEvent->keysym.sym, 1);
					break;
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_ACTIVEEVENT:
					game_hasfocus = event.active.state != 2; //TODO better focus detection
			}
		}
		
		++frames;
		game_render();
		
		for(int y = 0; y < game_screen.h; ++y){
			for(int x = 0; x < game_screen.w; ++x){
				pixel.x = x*SCALE;
				pixel.y = y*SCALE;
				
				int screen_px = game_screen.pixels[y * game_screen.w + x];
				SDL_FillRect(surface, &pixel, game_colors[screen_px]);
			}
		}
		
		SDL_Flip(surface);
		
		if(now - lastPrinted > 1000000){
			printf("%d ticks, %d fps\n", ticks, frames);
			ticks = 0;
			frames = 0;
			lastPrinted = now;
		}
		
		lastTime = now; //not like in java
	}
	
	QUIT:
	// Quit SDL
	SDL_Quit();
	delete_screen(&game_screen);
	//TODO delete_screen(&game_lightScreen);
	for(int i = 0; i < 5; ++i){
		printf("Freeing level %d\n", i);
		level_free(game_levels + i);
	}
	return ret;
}
