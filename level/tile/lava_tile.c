#include "tile.h"
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

	if (!u && !l) render_screen(screen, x * 16 + 0, y * 16 + 0, random_next_int(&wRandom, 4), col, random_next_int(&wRandom, 4));
	else render_screen(screen, x * 16 + 0, y * 16 + 0, (l ? 14 : 15) + (u ? 0 : 1) * 32, (su || sl) ? transitionColor2 : transitionColor1, 0);

	if (!u && !r) render_screen(screen, x * 16 + 8, y * 16 + 0, random_next_int(&wRandom, 4), col, random_next_int(&wRandom, 4));
	else render_screen(screen, x * 16 + 8, y * 16 + 0, (r ? 16 : 15) + (u ? 0 : 1) * 32, (su || sr) ? transitionColor2 : transitionColor1, 0);

	if (!d && !l) render_screen(screen, x * 16 + 0, y * 16 + 8, random_next_int(&wRandom, 4), col, random_next_int(&wRandom, 4));
	else render_screen(screen, x * 16 + 0, y * 16 + 8, (l ? 14 : 15) + (d ? 2 : 1) * 32, (sd || sl) ? transitionColor2 : transitionColor1, 0);
	
	if (!d && !r) render_screen(screen, x * 16 + 8, y * 16 + 8, random_next_int(&wRandom, 4), col, random_next_int(&wRandom, 4));
	else render_screen(screen, x * 16 + 8, y * 16 + 8, (r ? 16 : 15) + (d ? 2 : 1) * 32, (sd || sr) ? transitionColor2 : transitionColor1, 0);
}

void lavatile_tick(TileID id, Level* level, int xt, int yt){
	int xn = xt;
	int yn = yt;
	
	if(random_next_boolean(&trandom)) xn += random_next_int(&trandom, 2) * 2 - 1;
	else yn += random_next_int(&trandom, 2) * 2 - 1;
	
	if(level_get_tile(level, xn, yn) == HOLE) level_set_tile(level, xn, yn, id, 0);
}

//TODO mayPass
