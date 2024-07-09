#include "tile.h"
#include <gfx/color.h>

char dirttile_interact(TileID id, Level* level, int xt, int yt, struct _Player* player, struct _Item* item, int attackDir){
	/*TODO if (item instanceof ToolItem) {
			ToolItem tool = (ToolItem) item;
			if (tool.type == ToolType.shovel) {
				if (player.payStamina(4 - tool.level)) {
					level.setTile(xt, yt, Tile.hole, 0);
					level.add(new ItemEntity(new ResourceItem(Resource.dirt), xt * 16 + random.nextInt(10) + 3, yt * 16 + random.nextInt(10) + 3));
					Sound.monsterHurt.play();
					return true;
				}
			}
			if (tool.type == ToolType.hoe) {
				if (player.payStamina(4 - tool.level)) {
					level.setTile(xt, yt, Tile.farmland, 0);
					Sound.monsterHurt.play();
					return true;
				}
			}
		}
	}*/
	return 0;
}

void dirttile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(level->dirtColor, level->dirtColor, level->dirtColor - 111, level->dirtColor - 111);
	
	render_screen(screen, x*16 + 0, y * 16 + 0, 0, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 0, 1, col, 0);
	render_screen(screen, x*16 + 0, y * 16 + 8, 2, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 8, 3, col, 0);
}
