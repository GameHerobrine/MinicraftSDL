#include "../utils/javarandom.h"
#include "../utils/utils.h"
#include "../gfx/screen.h"
#include "tile/tile.h"
#include "level.h"
#include "levelgen/levelgen.h"

void level_init(Level* lvl, int w, int h, int level, Level* parent){
	random_set_seed(&lvl->random, getTimeUS() / 1000);
	lvl->dirtColor = level < 0 ? 222 : 322;
	lvl->grassColor = 141;
	lvl->sandColor = 550;
	lvl->monsterDensity = 8;
	
	lvl->depth = level;
	lvl->w = w;
	lvl->h = h;
	
	if(level == 0){
		createAndValidateTopMap(&lvl->tiles, &lvl->data, w, h);
	}else if(level < 0){
		createAndValidateUndergroundMap(&lvl->tiles, &lvl->data, w, h, -level);
		lvl->monsterDensity = 4;
	}else{
		createAndValidateSkyMap(&lvl->tiles, &lvl->data, w, h);
		lvl->monsterDensity = 4;
	}
	
	if(parent){
		for(int y = 0; y < h; ++y){
			for(int x = 0; x < w; ++x){
				//if() TODO level_get_tile();
			}
		}
	}
	
	//TODO entitiesInTile
	
	if(level == 1){
		//TODO spawn AirWizard
	}
}

void level_renderBackground(Level* level, Screen* screen, int xScroll, int yScroll){
	int xo = xScroll >> 4;
	int yo = yScroll >> 4;
	int w = (screen->w + 15) >> 4;
	int h = (screen->h + 15) >> 4;
	
	screen_set_offset(screen, xScroll, yScroll);
	for(int y = yo; y <= h + yo; ++y){
		for(int x = xo; x <= w + xo; ++x){
			unsigned char tile = level_get_tile(level, x, y);
			tile_render(tile, screen, level, x, y);
		}
	}
	
	screen_set_offset(screen, 0, 0);
	
}

//TODO renderSprites

void renderLight(Level* level, Screen* screen, int xScroll, int yScroll){
	int xo = xScroll >> 4;
	int yo = yScroll >> 4;
	int w = (screen->w + 15) >> 4;
	int h = (screen->h + 15) >> 4;
	
	screen_set_offset(screen, xScroll, yScroll);
	
	int r = 4;
	for(int y = yo - r; y <= h + yo + r; ++y){
		for(int x = xo - r; x <= w + xo + r; ++x){
			if(x < 0 || y < 0 || x >= level->w || y >= level->h) continue;
			//TODO light from entity
			
			//TODO light from blocks
		}
	}
	
	screen_set_offset(screen, 0, 0);
}


//TODO sortAndRender(Screen*, List<Entity>)

unsigned char level_get_tile(Level* level, int x, int y){
	if(x < 0 || y < 0 || x >= level->w || y >= level->h) return ROCK;
	return level->tiles[x + y*level->w];
}
void level_set_tile(Level* level, int x, int y, int id, int data){
	if(x < 0 || y < 0 || x >= level->w || y >= level->h) return;
	level->tiles[x + y*level->w] = id;
	level->data[x + y*level->w] = data;
}

unsigned char level_get_data(Level* level, int x, int y){
	if(x < 0 || y < 0 || x >= level->w || y >= level->h) return 0;
	return level->data[x + y*level->w];
}

void level_set_data(Level* level, int x, int y, int val){
	if(x < 0 || y < 0 || x >= level->w || y >= level->h) return;
	level->data[x + y*level->w] = val;
}

//TODO add(Entity*)
//TODO remove(Entity*)
//TODO insertEntity
//TODO removeEntity
//TODO trySpawn
//TODO getEntities()

void level_tick(Level* level){
	//TODO level_tick
}

void level_free(Level* lvl){
	if(lvl->tiles) free(lvl->tiles);
	if(lvl->data) free(lvl->data);
	
	
}
