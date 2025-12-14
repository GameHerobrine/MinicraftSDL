#include "tile.h";
#include <gfx/color.h>
void stairstile_init(TileID id, char leadsUp){
	tile_init(id);
	tiles[id].add.stairs.leadsUp = leadsUp;
}

void stairstile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int color = getColor4(level->dirtColor, 000, 333, 444);
	int xt = tiles[id].add.stairs.leadsUp ? 2 : 0;
	unsigned int spr = (id) | ((level->depth < 0) << 8) | (xt << 9);
	if(screen_get_sprite(x, y) != spr) {
		screen_set_sprite(x, y, spr);
		render_to_global(screen, x * 16 + 0, y * 16 + 0, xt + 2 * 32, color, 0);
		render_to_global(screen, x * 16 + 8, y * 16 + 0, xt + 1 + 2 * 32, color, 0);
		render_to_global(screen, x * 16 + 0, y * 16 + 8, xt + 3 * 32, color, 0);
		render_to_global(screen, x * 16 + 8, y * 16 + 8, xt + 1 + 3 * 32, color, 0);
	}
}
