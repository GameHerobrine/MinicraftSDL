#include "tile.h"

void sandtile_init(TileID id){
	tile_init(id);
	tiles[id].connectsToSand = 1;
}

void sandtile_tick(TileID id, Level* level, int xt, int yt){
	int damage = level_get_data(level, xt, yt);
	if(damage) level_set_data(level, xt, yt, damage - 1);
}

//TODO steppedOn(entity instance of Mob -> level.setData(x, y, 10)), interact
void sandtile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(level->sandColor + 2, level->sandColor, level->sandColor - 110, level->sandColor - 110);
	int transitionColor = getColor4(level->sandColor - 110, level->sandColor, level->sandColor - 110, level->dirtColor);

	char u = !tiles[level_get_tile(level, x, y - 1)].connectsToSand;
	char d = !tiles[level_get_tile(level, x, y + 1)].connectsToSand;
	char l = !tiles[level_get_tile(level, x - 1, y)].connectsToSand;
	char r = !tiles[level_get_tile(level, x + 1, y)].connectsToSand;
	char steppedOn = level_get_data(level, x, y) > 0;

	if (!u && !l){
		if (!steppedOn) render_screen(screen, x * 16 + 0, y * 16 + 0, 0, col, 0);
		else render_screen(screen, x * 16 + 0, y * 16 + 0, 3 + 1 * 32, col, 0);
	} else render_screen(screen, x * 16 + 0, y * 16 + 0, (l ? 11 : 12) + (u ? 0 : 1) * 32, transitionColor, 0);

	if (!u && !r) render_screen(screen, x * 16 + 8, y * 16 + 0, 1, col, 0);
	else render_screen(screen, x * 16 + 8, y * 16 + 0, (r ? 13 : 12) + (u ? 0 : 1) * 32, transitionColor, 0);

	if (!d && !l) render_screen(screen, x * 16 + 0, y * 16 + 8, 2, col, 0);
	else render_screen(screen, x * 16 + 0, y * 16 + 8, (l ? 11 : 12) + (d ? 2 : 1) * 32, transitionColor, 0);
	
	if (!d && !r){
		if (!steppedOn) render_screen(screen, x * 16 + 8, y * 16 + 8, 3, col, 0);
		else render_screen(screen, x * 16 + 8, y * 16 + 8, 3 + 1 * 32, col, 0);
	}else render_screen(screen, x * 16 + 8, y * 16 + 8, (r ? 13 : 12) + (d ? 2 : 1) * 32, transitionColor, 0);
}
