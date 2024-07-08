#include "tile.h"
#include <gfx/color.h>
#include <entity/particle/smashparticle.h>
void cactustile_init(TileID id){
	tile_init(id);
	tiles[id].connectsToSand = 1;
}

//TODO bumpedInto

void cactustile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(20, 40, 50, level->sandColor);
	
	render_screen(screen, x*16 + 0, y * 16 + 0, 8 + 2 * 32, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 0, 9 + 2 * 32, col, 0);
	render_screen(screen, x*16 + 0, y * 16 + 8, 8 + 3 * 32, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 8, 9 + 3 * 32, col, 0);
}



void cactus_hurt(TileID id, Level* level, int x, int y, Mob* source, int dmg, int attackDir){
	int damage = level_get_data(level, x, y) + dmg;

	SmashParticle* smash = malloc(sizeof(SmashParticle));
	smashparticle_create(smash, x * 16 + 8, y*16+8);
	level_addEntity(level, smash);
	//TODO level.add(new TextParticle("" + dmg, x * 16 + 8, y * 16 + 8, Color.get(-1, 500, 500, 500)));
	if(damage >= 10){
		int count = random_next_int(&tiles[id].random, 2) + 1;
		for(int i = 0; i < count; ++i){
			//TODO: level.add(new ItemEntity(new ResourceItem(Resource.cactusFlower), x * 16 + random.nextInt(10) + 3, y * 16 + random.nextInt(10) + 3));
		}
		level_set_tile(level, x, y, SAND, 0);
	}else{
		level_set_data(level, x, y, damage);
	}
}
void cactustile_tick(TileID id, Level* level, int xt, int yt){
	int damage = level_get_data(level, xt, yt);
	if(damage) level_set_data(level, xt, yt, damage - 1);
}
