#include "tile.h"
#include <entity/itementity.h>

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

void flowertile_hurt(TileID id, Level* level, int x, int y, Mob* source, int dmg, int attackDir){
	Random* random = &tiles[id].random;
	int count = random_next_int(random, 2) + 1;
	for (int i = 0; i < count; i++) {
		ItemEntity* ent = malloc(sizeof(ItemEntity));
		Item res;
		resourceitem_create(&res, &flower);
		int xx = x * 16 + random_next_int(random, 10) + 3;
		int yy = y * 16 + random_next_int(random, 10) + 3;
		itementity_create(ent, res, xx, yy);
		level_addEntity(level, ent);
	}
	level_set_tile(level, x, y, GRASS, 0);
}


//TODO interact
