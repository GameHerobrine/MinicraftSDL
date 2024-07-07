#include "tile.h"
#include <gfx/color.h>
//TODO override interact, tick, steppedOn

void farmlandtile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(level->dirtColor - 121, level->dirtColor - 11, level->dirtColor, level->dirtColor + 111);
	
	render_screen(screen, x*16 + 0, y * 16 + 0, 2 + 32, col, 1);
	render_screen(screen, x*16 + 8, y * 16 + 0, 2 + 32, col, 0);
	render_screen(screen, x*16 + 0, y * 16 + 8, 2 + 32, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 8, 2 + 32, col, 1);
}

void farmland_tick(TileID id, Level* level, int xt, int yt){
	int age = level_get_data(level, xt, yt);
	if(age < 5) level_set_data(level, xt, yt, age + 1);
}
