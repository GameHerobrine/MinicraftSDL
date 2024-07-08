#include "tile.h"
#include <gfx/color.h>
#include <entity/particle/smashparticle.h>
#include <entity/particle/textparticle.h>
//TODO override interact

void rocktile_hurt(TileID id, Level* level, int x, int y, Mob* source, int dmg, int attackDir){
	int damage = level_get_data(level, x, y) + dmg;

	SmashParticle* smash = malloc(sizeof(SmashParticle));
	smashparticle_create(smash, x * 16 + 8, y*16+8);
	level_addEntity(level, smash);

	TextParticle* txt = malloc(sizeof(TextParticle));
	char* tx_ = malloc(16);
	sprintf(tx_, "%d\00", dmg);
	textparticle_create(txt, tx_, x*16 + 8, y*16 + 8, getColor4(-1, 500, 500, 500));
	level_addEntity(level, txt);

	if(damage >= 50){
		/*TODO: int count = random.nextInt(4) + 1;
		for (int i = 0; i < count; i++) {
			level.add(new ItemEntity(new ResourceItem(Resource.stone), x * 16 + random.nextInt(10) + 3, y * 16 + random.nextInt(10) + 3));
		}
		count = random.nextInt(2);
		for (int i = 0; i < count; i++) {
			level.add(new ItemEntity(new ResourceItem(Resource.coal), x * 16 + random.nextInt(10) + 3, y * 16 + random.nextInt(10) + 3));
		}*/
		level_set_tile(level, x, y, DIRT, 0);
	}else{
		level_set_data(level, x, y, damage);
	}
}

void rocktile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(444, 444, 333, 333);
	int transitionColor = getColor4(111, 444, 555, level->dirtColor);

	char u = level_get_tile(level, x, y - 1) != id;
	char d = level_get_tile(level, x, y + 1) != id;
	char l = level_get_tile(level, x - 1, y) != id;
	char r = level_get_tile(level, x + 1, y) != id;
	
	char ul = level_get_tile(level, x - 1, y - 1) != id;
	char dl = level_get_tile(level, x - 1, y + 1) != id;
	char ur = level_get_tile(level, x + 1, y - 1) != id;
	char dr = level_get_tile(level, x + 1, y + 1) != id;

	if (!u && !l){
		if (!ul) render_screen(screen, x * 16 + 0, y * 16 + 0, 0, col, 0);
		else render_screen(screen, x * 16 + 0, y * 16 + 0, 7 + 0 * 32, transitionColor, 3);
	}else render_screen(screen, x * 16 + 0, y * 16 + 0, (l ? 6 : 5) + (u ? 2 : 1) * 32, transitionColor, 3);

	if (!u && !r){
		if (!ur) render_screen(screen, x * 16 + 8, y * 16 + 0, 1, col, 0);
		else render_screen(screen, x * 16 + 8, y * 16 + 0, 8 + 0 * 32, transitionColor, 3);
	}else render_screen(screen, x * 16 + 8, y * 16 + 0, (r ? 4 : 5) + (u ? 2 : 1) * 32, transitionColor, 3);

	if (!d && !l){
		if (!dl) render_screen(screen, x * 16 + 0, y * 16 + 8, 2, col, 0);
		else render_screen(screen, x * 16 + 0, y * 16 + 8, 7 + 1 * 32, transitionColor, 3);
	}else render_screen(screen, x * 16 + 0, y * 16 + 8, (l ? 6 : 5) + (d ? 0 : 1) * 32, transitionColor, 3);
	
	if (!d && !r){
		if (!dr) render_screen(screen, x * 16 + 8, y * 16 + 8, 3, col, 0);
		else render_screen(screen, x * 16 + 8, y * 16 + 8, 8 + 1 * 32, transitionColor, 3);
	}else render_screen(screen, x * 16 + 8, y * 16 + 8, (r ? 4 : 5) + (d ? 0 : 1) * 32, transitionColor, 3);
}

void rocktile_tick(TileID id, Level* level, int xt, int yt){
	int damage = level_get_data(level, xt, yt);
	if(damage) level_set_data(level, xt, yt, damage - 1);
}
