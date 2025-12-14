#include "tile.h"
#include <gfx/color.h>
static Random wRandom;
static Random trandom;

void lavatile_init(TileID id){
	tile_init(id);
	
	Tile* tile = tiles + id;
	tile->connectsToSand = tile->connectsToLava = 1;
	random_set_seed(&trandom, getTimeUS() / 1000); 
}

void lavatile_render(TileID id, Screen* screen, Level* level, int x, int y){
	random_set_seed(&wRandom, ((tile_tickCount + (x / 2 - y) * 4311) / 10 * 54687121 + x * 3271612 + y * 3412987161));
	int col = getColor4(500, 500, 520, 550);
	int transitionColor1 = getColor4(3, 500, level->dirtColor - 111, level->dirtColor);
	int transitionColor2 = getColor4(3, 500, level->sandColor - 110, level->sandColor);

	char u = !tiles[level_get_tile(level, x, y - 1)].connectsToLava;
	char d = !tiles[level_get_tile(level, x, y + 1)].connectsToLava;
	char l = !tiles[level_get_tile(level, x - 1, y)].connectsToLava;
	char r = !tiles[level_get_tile(level, x + 1, y)].connectsToLava;

	char su = u && tiles[level_get_tile(level, x, y - 1)].connectsToSand;
	char sd = d && tiles[level_get_tile(level, x, y + 1)].connectsToSand;
	char sl = l && tiles[level_get_tile(level, x - 1, y)].connectsToSand;
	char sr = r && tiles[level_get_tile(level, x + 1, y)].connectsToSand;
	int a = 0, b = 0, c = 0, dd = 0, e = 0, f = 0, g = 0, h = 0;
	if(!u && !l) {
		a = random_next_int(&wRandom, 4);
		b = random_next_int(&wRandom, 4);
	}
	if(!u && !r) {
		c = random_next_int(&wRandom, 4);
		dd = random_next_int(&wRandom, 4);
	}
	if(!d && !l) {
		e = random_next_int(&wRandom, 4);
		f = random_next_int(&wRandom, 4);
	}
	if(!d && !r) {
		g = random_next_int(&wRandom, 4);
		h = random_next_int(&wRandom, 4);
	}

	unsigned int spr = LAVA | (u << 8) | (d << 9) | (l << 10) | (r << 11) | (su << 12) | (sd << 13) | (sl << 14) | (sr << 15) | (a << 16) | (b << 18) | (c << 20) | (dd << 22) | (e << 24) | (f << 26) | (g << 28) | (h << 28);
	if(screen_get_sprite(x, y) != spr) {
		screen_set_sprite(x, y, spr);
		if (!u && !l) render_to_global(screen, x * 16 + 0, y * 16 + 0, a, col, b);
		else render_to_global(screen, x * 16 + 0, y * 16 + 0, (l ? 14 : 15) + (u ? 0 : 1) * 32, (su || sl) ? transitionColor2 : transitionColor1, 0);

		if (!u && !r) render_to_global(screen, x * 16 + 8, y * 16 + 0, c, col, dd);
		else render_to_global(screen, x * 16 + 8, y * 16 + 0, (r ? 16 : 15) + (u ? 0 : 1) * 32, (su || sr) ? transitionColor2 : transitionColor1, 0);

		if (!d && !l) render_to_global(screen, x * 16 + 0, y * 16 + 8, e, col, f);
		else render_to_global(screen, x * 16 + 0, y * 16 + 8, (l ? 14 : 15) + (d ? 2 : 1) * 32, (sd || sl) ? transitionColor2 : transitionColor1, 0);

		if (!d && !r) render_to_global(screen, x * 16 + 8, y * 16 + 8, g, col, h);
		else render_to_global(screen, x * 16 + 8, y * 16 + 8, (r ? 16 : 15) + (d ? 2 : 1) * 32, (sd || sr) ? transitionColor2 : transitionColor1, 0);
	}
}

void lavatile_tick(TileID id, Level* level, int xt, int yt){
	int xn = xt;
	int yn = yt;
	
	if(random_next_boolean(&trandom)) xn += random_next_int(&trandom, 2) * 2 - 1;
	else yn += random_next_int(&trandom, 2) * 2 - 1;
	
	if(level_get_tile(level, xn, yn) == HOLE) level_set_tile(level, xn, yn, id, 0);
}
