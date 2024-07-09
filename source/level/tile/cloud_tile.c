#include "tile.h"
#include <gfx/color.h>

void cloudtile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(444, 444, 555, 555);
	int transitionColor = getColor4(333, 444, 555, -1);
	//TODO broken
	char u = level_get_tile(level, x, y - 1) == INFINITE_FALL;
	char d = level_get_tile(level, x, y + 1) == INFINITE_FALL;
	char l = level_get_tile(level, x - 1, y) == INFINITE_FALL;
	char r = level_get_tile(level, x + 1, y) == INFINITE_FALL;
	
	char ul = level_get_tile(level, x - 1, y - 1) == INFINITE_FALL;
	char dl = level_get_tile(level, x - 1, y + 1) == INFINITE_FALL;
	char ur = level_get_tile(level, x + 1, y - 1) == INFINITE_FALL;
	char dr = level_get_tile(level, x + 1, y + 1) == INFINITE_FALL;
	
	if(!u && !l){
		if(!ul) render_screen(screen, x * 16 + 0, y * 16 + 0, 17, col, 0);
		else render_screen(screen, x * 16 + 0, y * 16 + 0, 7 + 0 * 32, transitionColor, 3);
	}else{
		render_screen(screen, x * 16 + 0, y * 16 + 0, (l ? 6 : 5) + (u ? 2 : 1) * 32, transitionColor, 3);
	}
	
	if(!u && !r){
		if(!ur) render_screen(screen, x * 16 + 0, y * 16 + 0, 18, col, 0);
		else render_screen(screen, x * 16 + 8, y * 16 + 0, 8 + 0 * 32, transitionColor, 3);
	}else{
		render_screen(screen, x * 16 + 8, y * 16 + 0, (r ? 4 : 5) + (u ? 2 : 1) * 32, transitionColor, 3);
	}
	
	if(!d && !l){
		if(!dl) render_screen(screen, x * 16 + 0, y * 16 + 8, 20, col, 0);
		else render_screen(screen, x * 16 + 0, y * 16 + 8, 7 + 1 * 32, transitionColor, 3);
	}else{
		render_screen(screen, x * 16 + 0, y * 16 + 8, (l ? 6 : 5) + (d ? 0 : 1) * 32, transitionColor, 3);
	}
	
	if(!d && !r){
		if(!dr) render_screen(screen, x * 16 + 8, y * 16 + 8, 19, col, 0);
		else render_screen(screen, x * 16 + 8, y * 16 + 8, 8 + 1 * 32, transitionColor, 3);
	}else{
		render_screen(screen, x * 16 + 8, y * 16 + 8, (r ? 4 : 5) + (d ? 0 : 1) * 32, transitionColor, 3);
	}
}

char cloudtile_interact(TileID id, Level* level, int xt, int yt, struct _Player* player, struct _Item* item, int attackDir){
	/*TODO if (item instanceof ToolItem) {
			ToolItem tool = (ToolItem) item;
			if (tool.type == ToolType.shovel) {
				if (player.payStamina(5)) {
					// level.setTile(xt, yt, Tile.infiniteFall, 0);
					int count = random.nextInt(2) + 1;
					for (int i = 0; i < count; i++) {
						level.add(new ItemEntity(new ResourceItem(Resource.cloud), xt * 16 + random.nextInt(10) + 3, yt * 16 + random.nextInt(10) + 3));
					}
					return true;
				}
			}
		}
	}*/
	return 0;
}
