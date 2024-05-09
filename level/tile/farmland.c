#include "tile.h"

//TODO override interact, tick, steppedOn

void farmlandtile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(level->dirtColor - 121, level->dirtColor - 11, level->dirtColor, level->dirtColor + 111);
	
	render_screen(screen, x*16 + 0, y * 16 + 0, 2 + 32, col, 1);
	render_screen(screen, x*16 + 8, y * 16 + 0, 2 + 32, col, 0);
	render_screen(screen, x*16 + 0, y * 16 + 8, 2 + 32, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 8, 2 + 32, col, 1);
}
