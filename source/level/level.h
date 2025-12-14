#ifndef LEVEL_LEVEL_H_
#define LEVEL_LEVEL_H_
#include <gfx/screen.h>
#include <utils/arraylist.h>
#include <utils/javarandom.h>
#include <entity/entity.h>
#include <level/tile/tileids.h>

typedef struct _Level{
	Random random;
	int w, h;
	unsigned char* tiles;
	unsigned char* data;
	ArrayList* entitiesInTiles;
	int grassColor;
	int dirtColor;
	int sandColor;
	int depth;
	int monsterDensity;
	ArrayList entities;
} Level;

void level_trySpawn(Level* level, int count);
void level_init(Level* lvl, int w, int h, int level, Level* parent);
static inline unsigned char level_get_tile(Level* level, int x, int y){
	if(x < 0 || y < 0 || x >= level->w || y >= level->h) return ROCK;
	return level->tiles[x + y*level->w];
}
unsigned char level_get_data(Level* level, int x, int y);
void level_renderBackground(Level* level, Screen* screen, int xScroll, int yScroll);
void level_tick(Level* level);
void level_set_tile(Level* level, int x, int y, int id, int data);
void level_set_data(Level* level, int x, int y, int val);
void level_renderSprites(Level* level, Screen* screen, int xScroll, int yScroll);
void level_removeEntity(Level* level, int x, int y, Entity* entity);
void level_addEntity(Level* level, Entity* entity);
void level_insertEntity(Level* level, int x, int y, Entity* entity);
void level_getEntities(Level* level, ArrayList* list, int x0, int y0, int x1, int y1);

void level_free(Level* lvl);
#endif /* LEVEL_LEVEL_H_ */
