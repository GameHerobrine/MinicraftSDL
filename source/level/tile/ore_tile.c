#include "tile.h"
#include <item/resource/resource.h>
#include <gfx/color.h>
#include <gfx/color.h>

void oretile_init(TileID id, Resource* toDrop){
	tile_init(id);
	Tile* t = tiles + id;
	t->add.ore.toDrop = toDrop;
	t->add.ore.color = toDrop->color & 0xffff00;
}
void oretile_render(TileID id, Screen* screen, Level* level, int x, int y){
	tiles[id].add.ore.color = (tiles[id].add.ore.toDrop->color & 0xffffff00) + getColor(level->dirtColor);
	
	render_screen(screen, x * 16 + 0, y * 16 + 0, 17 + 1 * 32, tiles[id].add.ore.color, 0);
	render_screen(screen, x * 16 + 8, y * 16 + 0, 18 + 1 * 32, tiles[id].add.ore.color, 0);
	render_screen(screen, x * 16 + 0, y * 16 + 8, 17 + 2 * 32, tiles[id].add.ore.color, 0);
	render_screen(screen, x * 16 + 8, y * 16 + 8, 18 + 2 * 32, tiles[id].add.ore.color, 0);
}

char oretile_interact(TileID id, Level* level, int xt, int yt, struct _Player* player, struct _Item* item, int attackDir){
	/*TODO if (item instanceof ToolItem) {
			ToolItem tool = (ToolItem) item;
			if (tool.type == ToolType.pickaxe) {
				if (player.payStamina(6 - tool.level)) {
					hurt(level, xt, yt, 1);
					return true;
				}
			}
		}*/
	return 0;
}

//TODO hurt: Level*, Mob*
//TODO custom hurt
//TODO bumpedInto -> Level*, Entity*
