#include "tile.h"

//TODO override interact, mayPass, hurt + add a method hurt

void hardrocktile_tick(TileID id, Level* level, int xt, int yt){
	int damage = level_get_data(level, xt, yt);
	if(damage) level_set_data(level, xt, yt, damage - 1);
}

void hardrocktile_render(TileID id, Screen* screen, Level* level, int x, int y){
	
	int col = getColor4(334, 334, 223, 223);
	int transitionColor = getColor4(001, 334, 445, level->dirtColor);
	
	char u = level_get_tile(level, x, y - 1) != id;
	char d = level_get_tile(level, x, y + 1) != id;
	char l = level_get_tile(level, x - 1, y) != id;
	char r = level_get_tile(level, x + 1, y) != id;
	
	char ul = level_get_tile(level, x - 1, y - 1) != id;
	char dl = level_get_tile(level, x - 1, y + 1) != id;
	char ur = level_get_tile(level, x + 1, y - 1) != id;
	char dr = level_get_tile(level, x + 1, y + 1) != id;
	
	if(!u && !l){
		if(!ul) render_screen(screen, x * 16 + 0, y * 16 + 0, 0, col, 0);
		else render_screen(screen, x * 16 + 0, y * 16 + 0, 7 + 0 * 32, transitionColor, 3);
	}else render_screen(screen, x * 16 + 0, y * 16 + 0, (l ? 6 : 5) + (u ? 2 : 1) * 32, transitionColor, 3);

	if(!u && !r){
		if(!ur) render_screen(screen, x * 16 + 8, y * 16 + 0, 1, col, 0);
		else render_screen(screen, x * 16 + 8, y * 16 + 0, 8 + 0 * 32, transitionColor, 3);
	}else render_screen(screen, x * 16 + 8, y * 16 + 0, (r ? 4 : 5) + (u ? 2 : 1) * 32, transitionColor, 3);
	
	if(!d && !l){
		if(!dl) render_screen(screen, x * 16 + 0, y * 16 + 8, 2, col, 0);
		else render_screen(screen, x * 16 + 0, y * 16 + 8, 7 + 1 * 32, transitionColor, 3);
	}else render_screen(screen, x * 16 + 0, y * 16 + 8, (l ? 6 : 5) + (d ? 0 : 1) * 32, transitionColor, 3);
	
	if(!d && !r){
		if(!dr) render_screen(screen, x * 16 + 8, y * 16 + 8, 3, col, 0);
		else render_screen(screen, x * 16 + 8, y * 16 + 8, 8 + 1 * 32, transitionColor, 3);
	}else render_screen(screen, x * 16 + 8, y * 16 + 8, (r ? 4 : 5) + (d ? 0 : 1) * 32, transitionColor, 3);
}
