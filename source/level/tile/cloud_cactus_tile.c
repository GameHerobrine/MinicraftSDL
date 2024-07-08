#include "tile.h"
#include <gfx/color.h>
#include <entity/particle/smashparticle.h>
#include <entity/particle/textparticle.h>
//TODO interact, bumpedInto + add hurt

void cloudcactustile_render(TileID id, Screen* screen, Level* level, int x, int y){
	int col = getColor4(444, 111, 333, 555);
	
	render_screen(screen, x*16 + 0, y * 16 + 0, 17 + 1 * 32, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 0, 18 + 1 * 32, col, 0);
	render_screen(screen, x*16 + 0, y * 16 + 8, 17 + 2 * 32, col, 0);
	render_screen(screen, x*16 + 8, y * 16 + 8, 18 + 2 * 32, col, 0);
}

void cloudcactus_hurt(TileID id, Level* level, int x, int y, Mob* source, int dmg, int attackDir){
	int damage = level_get_data(level, x, y) + 1;
	SmashParticle* smash = malloc(sizeof(SmashParticle));
	smashparticle_create(smash, x * 16 + 8, y*16+8);
	level_addEntity(level, smash);

	TextParticle* txt = malloc(sizeof(TextParticle));
	char* tx_ = malloc(16);
	sprintf(tx_, "%d\00", dmg);
	textparticle_create(txt, tx_, x*16 + 8, y*16 + 8, getColor4(-1, 500, 500, 500));
	level_addEntity(level, txt);

	if(dmg > 0){
		if(damage >= 10){
			level_set_tile(level, x, y, CLOUD, 0);
		}else{
			level_set_data(level, x, y, damage);
		}
	}
}