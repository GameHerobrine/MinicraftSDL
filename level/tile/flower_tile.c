#include "tile.h"

void flowertile_init(TileID id){
	tile_init(id);
	tiles[id].connectsToGrass = 1;
}
void flowertile_render(TileID id, Screen* screen, Level* level, int x, int y){
	grasstile_render(id, screen, level, x, y);
	
	int data = level_get_data(level, x, y);
	int shape = (data / 16) % 2;
	int flowerCol = getColor4(10, level->grassColor, 555, 440);
	
	if(shape == 0) render_screen(screen, x * 16 + 0, y * 16 + 0, 1 + 1 * 32, flowerCol, 0);
	if(shape == 1) render_screen(screen, x * 16 + 8, y * 16 + 0, 1 + 1 * 32, flowerCol, 0);
	
	if(shape == 1) render_screen(screen, x * 16 + 0, y * 16 + 8, 1 + 1 * 32, flowerCol, 0);
	if(shape == 0) render_screen(screen, x * 16 + 8, y * 16 + 8, 1 + 1 * 32, flowerCol, 0);
	
}


//TODO interact, hurt
