#include "tile.h"

void cactustile_init(TileID id){
	tile_init(id);
	tiles[id].connectsToSand = 1;
}

//TODO mayPass -> false, hurt, bumpedInto, tick

void cactustile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(20, 40, 50, level->sandColor);
	
	render_screen(screen, x*16 + 0, y * 16 + 0, 8 + 2 * 32, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 0, 9 + 2 * 32, col, 0);
	render_screen(screen, x*16 + 0, y * 16 + 8, 8 + 3 * 32, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 8, 9 + 3 * 32, col, 0);
}
