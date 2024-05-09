#include "tile.h"
#include "../../utils/javarandom.h"
static Random wRandom;

void watertile_init(TileID id){
	tile_init(id);
	
	Tile* tile = tiles + id;
	tile->connectsToSand = 1;
	tile->connectsToWater = 1;
}

void watertile_render(TileID id, Screen* screen, Level* level, int x, int y){
	random_set_seed(&wRandom, (tile_tickCount + (x / 2 - y) * 4311) / 10 * 54687121 + x * 3271612 + y * 3412987161);
	int col = getColor4(5, 5, 115, 115);
	int transitionColor1 = getColor4(3, 5, level->dirtColor - 111, level->dirtColor);
	int transitionColor2 = getColor4(3, 5, level->sandColor - 111, level->sandColor);
	
	char u = !tiles[level_get_tile(level, x, y - 1)].connectsToWater;
	char d = !tiles[level_get_tile(level, x, y + 1)].connectsToWater;
	char l = !tiles[level_get_tile(level, x - 1, y)].connectsToWater;
	char r = !tiles[level_get_tile(level, x + 1, y)].connectsToWater;
	
	char su = !tiles[level_get_tile(level, x, y - 1)].connectsToSand;
	char sd = !tiles[level_get_tile(level, x, y + 1)].connectsToSand;
	char sl = !tiles[level_get_tile(level, x - 1, y)].connectsToSand;
	char sr = !tiles[level_get_tile(level, x + 1, y)].connectsToSand;
	
	if(!u && !l) render_screen(screen, x * 16 + 0, y * 16 + 0, random_next_int(&wRandom, 4), col, random_next_int(&wRandom, 4));
	else render_screen(screen, x * 16 + 0, y * 16 + 0, (l ? 14 : 15) + (u ? 0 : 1) * 32, (su || sl) ? transitionColor2 : transitionColor1, 0);
	
	if(!u && !r) render_screen(screen, x * 16 + 8, y * 16 + 0, random_next_int(&wRandom, 4), col, random_next_int(&wRandom, 4));
	else render_screen(screen, x * 16 + 8, y * 16 + 0, (r ? 16 : 15) + (u ? 0 : 1) * 32, (su || sr) ? transitionColor2 : transitionColor1, 0);
	
	if(!d && !l) render_screen(screen, x * 16 + 0, y * 16 + 8, random_next_int(&wRandom, 4), col, random_next_int(&wRandom, 4));
	else render_screen(screen, x * 16 + 0, y * 16 + 8, (l ? 14 : 15) + (d ? 2 : 1) * 32, (sd || sl) ? transitionColor2 : transitionColor1, 0);
	
	if(!d && !r) render_screen(screen, x * 16 + 8, y * 16 + 8, random_next_int(&wRandom, 4), col, random_next_int(&wRandom, 4));
	else render_screen(screen, x * 16 + 8, y * 16 + 8, (r ? 16 : 15) + (d ? 2 : 1) * 32, (sd || sr) ? transitionColor2 : transitionColor1, 0);
}

//TODO override: mayPass, tick.
