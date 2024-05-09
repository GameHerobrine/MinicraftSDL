#include "tile.h"

void grasstile_init(TileID id){
	tile_init(id);
	Tile* t = tiles + id;
	
	t->connectsToGrass = 1;
}
void grasstile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(level->grassColor, level->grassColor, level->grassColor + level->grassColor + 111);
	int transitionColor = getColor4(level->grassColor - 111, level->grassColor, level->grassColor + 111, level->dirtColor);

	char u = !tiles[level_get_tile(level, x, y - 1)].connectsToGrass;
	char d = !tiles[level_get_tile(level, x, y + 1)].connectsToGrass;
	char l = !tiles[level_get_tile(level, x - 1, y)].connectsToGrass;
	char r = !tiles[level_get_tile(level, x + 1, y)].connectsToGrass;

	if (!u && !l) render_screen(screen, x * 16 + 0, y * 16 + 0, 0, col, 0);
	else render_screen(screen, x * 16 + 0, y * 16 + 0, (l ? 11 : 12) + (u ? 0 : 1) * 32, transitionColor, 0);

	if (!u && !r) render_screen(screen, x * 16 + 8, y * 16 + 0, 1, col, 0);
	else render_screen(screen, x * 16 + 8, y * 16 + 0, (r ? 13 : 12) + (u ? 0 : 1) * 32, transitionColor, 0);

	if (!d && !l) render_screen(screen, x * 16 + 0, y * 16 + 8, 2, col, 0);
	else render_screen(screen, x * 16 + 0, y * 16 + 8, (l ? 11 : 12) + (d ? 2 : 1) * 32, transitionColor, 0);
	
	if (!d && !r) render_screen(screen, x * 16 + 8, y * 16 + 8, 3, col, 0);
	else render_screen(screen, x * 16 + 8, y * 16 + 8, (r ? 13 : 12) + (d ? 2 : 1) * 32, transitionColor, 0);
}	
//TODO override tick, interact 
