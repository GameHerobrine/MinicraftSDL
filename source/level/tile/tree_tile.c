#include "tile.h"
#include <entity/particle/smashparticle.h>

void treetile_init(TileID id){
	tile_init(id);
	tiles[id].connectsToGrass = 1;
}
void treetile_hurt2(TileID id, Level* level, int x, int y, int dmg){
	/*TODO:
	 * int count = random.nextInt(10) == 0 ? 1 : 0;
			for (int i = 0; i < count; i++) {
				level.add(new ItemEntity(new ResourceItem(Resource.apple), x * 16 + random.nextInt(10) + 3, y * 16 + random.nextInt(10) + 3));
			}
	*/
	int damage = level_get_data(level, x, y) + dmg;
	SmashParticle* smash = malloc(sizeof(SmashParticle));
	smashparticle_create(smash, x * 16 + 8, y*16+8);
	level_addEntity(level, smash);
	//TODO: level.add(new TextParticle("" + dmg, x * 16 + 8, y * 16 + 8, Color.get(-1, 500, 500, 500)));
	if(damage >= 20){
		/*TODO:
		 * int count = random.nextInt(2) + 1;
		for (int i = 0; i < count; i++) {
			level.add(new ItemEntity(new ResourceItem(Resource.wood), x * 16 + random.nextInt(10) + 3, y * 16 + random.nextInt(10) + 3));
		}
		count = random.nextInt(random.nextInt(4) + 1);
		for (int i = 0; i < count; i++) {
			level.add(new ItemEntity(new ResourceItem(Resource.acorn), x * 16 + random.nextInt(10) + 3, y * 16 + random.nextInt(10) + 3));
		}
		*/
		level_set_tile(level, x, y, GRASS, 0);
	}else{
		level_set_data(level, x, y, damage);
	}
}
void treetile_hurt(TileID id, Level* level, int x, int y, Mob* source, int dmg, int attackDir){
	treetile_hurt2(id, level, x, y, dmg);
}

void treetile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(10, 30, 151, level->grassColor);
	int barkCol1 = getColor4(10, 30, 430, level->grassColor);
	int barkCol2 = getColor4(10, 30, 320, level->grassColor);
	
	char u = level_get_tile(level, x, y - 1) == id;
	char l = level_get_tile(level, x - 1, y) == id;
	char r = level_get_tile(level, x + 1, y) == id;
	char d = level_get_tile(level, x, y + 1) == id;
	
	char ul = level_get_tile(level, x - 1, y - 1) == id;
	char ur = level_get_tile(level, x + 1, y - 1) == id;
	char dl = level_get_tile(level, x - 1, y + 1) == id;
	char dr = level_get_tile(level, x + 1, y + 1) == id;
	
	if(u && ul && l) render_screen(screen, x * 16 + 0, y * 16 + 0, 10 + 1 * 32, col, 0);
	else render_screen(screen, x * 16 + 0, y * 16 + 0, 9 + 0 * 32, col, 0);
	
	if(u && ur && r) render_screen(screen, x * 16 + 8, y * 16 + 0, 10 + 2 * 32, barkCol2, 0);
	else render_screen(screen, x * 16 + 8, y * 16 + 0, 10 + 0 * 32, col, 0);
	
	if(d && dl && l) render_screen(screen, x * 16 + 0, y * 16 + 8, 10 + 2 * 32, barkCol2, 0);
	else render_screen(screen, x * 16 + 0, y * 16 + 8, 9 + 1 * 32, barkCol1, 0);
	
	if(d && dr && r) render_screen(screen, x * 16 + 8, y * 16 + 8, 10 + 1 * 32, col, 0);
	else render_screen(screen, x * 16 + 8, y * 16 + 8, 10 + 3 * 32, barkCol2, 0);
}

void treetile_tick(TileID id, Level* level, int xt, int yt){
	int damage = level_get_data(level, xt, yt);
	if(damage) level_set_data(level, xt, yt, damage - 1);
}

//TODO override: hurt, interact + private hurt(Level*, x, y, int dmg);

