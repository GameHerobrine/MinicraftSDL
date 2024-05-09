#include "tile.h"

//TODO override: interact

void dirttile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(level->dirtColor, level->dirtColor, level->dirtColor - 111, level->dirtColor - 111);
	
	render_screen(screen, x*16 + 0, y * 16 + 0, 0, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 0, 1, col, 0);
	render_screen(screen, x*16 + 0, y * 16 + 8, 2, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 8, 3, col, 0);
}
