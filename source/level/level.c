#include <utils/javarandom.h>
#include <utils/utils.h>
#include "../gfx/screen.h"
#include "tile/tile.h"
#include <utils/arraylist.h>
#include "level.h"
#include "levelgen/levelgen.h"

void level_init(Level* lvl, int w, int h, int level, Level* parent){
	random_set_seed(&lvl->random, getTimeMS());
	create_arraylist(&lvl->entities);
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
				if(level_get_tile(parent, x, y) == STAIRS_DOWN){
					level_set_tile(lvl, x, y, STAIRS_UP, 0);

					if(level == 0){
						level_set_tile(lvl, x - 1, y, (int)HARD_ROCK, 0);
						level_set_tile(lvl, x + 1, y, (int)HARD_ROCK, 0);
						level_set_tile(lvl, x, y - 1, (int)HARD_ROCK, 0);
						level_set_tile(lvl, x, y + 1, (int)HARD_ROCK, 0);
						level_set_tile(lvl, x - 1, y - 1, (int)HARD_ROCK, 0);
						level_set_tile(lvl, x - 1, y + 1, (int)HARD_ROCK, 0);
						level_set_tile(lvl, x + 1, y - 1, (int)HARD_ROCK, 0);
						level_set_tile(lvl, x + 1, y + 1, (int)HARD_ROCK, 0);
					}else{
						level_set_tile(lvl, x - 1, y, (int)DIRT, 0);
						level_set_tile(lvl, x + 1, y, (int)DIRT, 0);
						level_set_tile(lvl, x, y - 1, (int)DIRT, 0);
						level_set_tile(lvl, x, y + 1, (int)DIRT, 0);
						level_set_tile(lvl, x - 1, y - 1, (int)DIRT, 0);
						level_set_tile(lvl, x - 1, y + 1, (int)DIRT, 0);
						level_set_tile(lvl, x + 1, y - 1, (int)DIRT, 0);
						level_set_tile(lvl, x + 1, y + 1, (int)DIRT, 0);
					}
				}
			}
		}
	}
	
	lvl->entitiesInTiles = malloc(sizeof(ArrayList)*w*h);
	for(int i = 0; i < w*h; ++i){
		create_arraylist(lvl->entitiesInTiles + i);
	}

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

void level_renderSprites(Level* level, Screen* screen, int xScroll, int yScroll){

	int xo = xScroll >> 4;
	int yo = yScroll >> 4;
	int w = (screen->w + 15) >> 4;
	int h = (screen->h + 15) >> 4;

	screen_set_offset(screen, xScroll, yScroll);
	for(int y = yo; y < h+yo; ++y){
		for(int x = xo; x <= w+xo; ++x){
			//TODO renderSprites
		}
	}

	screen_set_offset(screen, 0, 0);
}



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
	//TODO trySpawn(1);
	
	for(int i = 0; i < level->w*level->h / 50; ++i){
		int xt = random_next_int(&level->random, level->w);
		int yt = random_next_int(&level->random, level->w);
		
		tile_tick(level_get_tile(level, xt, yt), level, xt, yt);
		
	}
	
	//TODO entities
	
}

void level_free(Level* lvl){
	if(lvl->tiles) free(lvl->tiles);
	if(lvl->data) free(lvl->data);
	if(lvl->entitiesInTiles){
		for(int i = 0; i < lvl->w*lvl->h; ++i){
			arraylist_remove_and_dealloc_each(lvl->entitiesInTiles + i);
		}
		free(lvl->entitiesInTiles);
	}
}
