#include "tile.h"
#include <gfx/color.h>

//TODO mayPass, hurt, interact, bumpedInto + add hurt

void cloudcactustile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(444, 111, 333, 555);
	
	render_screen(screen, x*16 + 0, y * 16 + 0, 17 + 1 * 32, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 0, 18 + 1 * 32, col, 0);
	render_screen(screen, x*16 + 0, y * 16 + 8, 17 + 2 * 32, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 8, 18 + 2 * 32, col, 0);
}
