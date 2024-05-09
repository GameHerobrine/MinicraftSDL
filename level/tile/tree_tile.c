#include "tile.h"

void treetile_init(TileID id){
	tile_init(id);
	tiles[id].connectsToGrass = 1;
}
void treetile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(10, 30, 151, level->grassColor);
	int barkCol1 = getColor4(10, 30, 430, level->grassColor);
	int barkCol2 = getColor4(10, 30, 320, level->grassColor);
	
	char u = level_get_tile(level, x, y - 1) == id;
	char l = level_get_tile(level, x - 1, y) == id;
	char r = level_get_tile(level, x + 1, y) == id;
	char d = level_get_tile(level, x, y + 1) == id;
	
	char ul = level_get_tile(level, x - 1, y - 1) == id;
	char ur = level_get_tile(level, x + 1, y - 1) == id;
	char dl = level_get_tile(level, x - 1, y + 1) == id;
	char dr = level_get_tile(level, x + 1, y + 1) == id;
	
	if(u && ul && l) render_screen(screen, x * 16 + 0, y * 16 + 0, 10 + 1 * 32, col, 0);
	else render_screen(screen, x * 16 + 0, y * 16 + 0, 9 + 0 * 32, col, 0);
	
	if(u && ur && r) render_screen(screen, x * 16 + 8, y * 16 + 0, 10 + 2 * 32, barkCol2, 0);
	else render_screen(screen, x * 16 + 8, y * 16 + 0, 10 + 0 * 32, col, 0);
	
	if(d && dl && l) render_screen(screen, x * 16 + 0, y * 16 + 8, 10 + 2 * 32, barkCol2, 0);
	else render_screen(screen, x * 16 + 0, y * 16 + 8, 9 + 1 * 32, barkCol1, 0);
	
	if(d && dr && r) render_screen(screen, x * 16 + 8, y * 16 + 8, 10 + 1 * 32, col, 0);
	else render_screen(screen, x * 16 + 8, y * 16 + 8, 10 + 3 * 32, barkCol2, 0);
}
//TODO override: render, tick, mayPass -> false, hurt, interact + private hurt(Level*, x, y, int dmg);

