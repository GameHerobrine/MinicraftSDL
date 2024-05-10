#include "tile.h"
static Random trandom;
void wheat_tile_init(TileID id){
	tile_init(id);
	random_set_seed(&trandom, getTimeUS() / 1000); 
}

//TODO tick, interact, steppedOn, hurt + add private harvest(Level* level, int x, int y);
void wheattile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int age = level_get_data(level, x, y);
	int col = getColor4(level->dirtColor - 121, level->dirtColor - 11, level->dirtColor, 50);
	int icon = age / 10;
	if (icon >= 3){
		col = getColor4(level->dirtColor - 121, level->dirtColor - 11, 50 + (icon) * 100, 40 + (icon - 3) * 2 * 100);
		if (age == 50) col = getColor4(0, 0, 50 + (icon) * 100, 40 + (icon - 3) * 2 * 100);
		icon = 3;
	}
	
	render_screen(screen, x * 16 + 0, y * 16 + 0, 4 + 3 * 32 + icon, col, 0);
	render_screen(screen, x * 16 + 8, y * 16 + 0, 4 + 3 * 32 + icon, col, 0);
	render_screen(screen, x * 16 + 0, y * 16 + 8, 4 + 3 * 32 + icon, col, 1);
	render_screen(screen, x * 16 + 8, y * 16 + 8, 4 + 3 * 32 + icon, col, 1);
}


void wheattile_tick(TileID id, Level* level, int xt, int yt){
	if(random_next_int(&trandom, 2) == 0) return;
	
	int age = level_get_data(level, xt, yt);
	if(age < 50) level_set_data(xt, yt, age + 1);
}
