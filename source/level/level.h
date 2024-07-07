#ifndef LEVEL_LEVEL_H_
#define LEVEL_LEVEL_H_
#include <gfx/screen.h>
#include "../utils/javarandom.h"


typedef struct level_{
	Random random;
	int w, h;
	unsigned char* tiles;
	unsigned char* data;
	//TODO Entity* -> ArrayList<Entity>[] entitiesInTiles
	int grassColor;
	int dirtColor;
	int sandColor;
	int depth;
	int monsterDensity;
	//TODO Entity* -> ArrayList entities
} Level;

void level_init(Level* lvl, int w, int h, int level, Level* parent);
unsigned char level_get_tile(Level* level, int x, int y);
unsigned char level_get_data(Level* level, int x, int y);
void level_renderBackground(Level* level, Screen* screen, int xScroll, int yScroll);
void level_tick(Level* level);
void level_set_data(Level* level, int x, int y, int val);
void level_renderSprites(Level* level, Screen* screen, int xScroll, int yScroll);

void level_free(Level* lvl);
#endif /* LEVEL_LEVEL_H_ */
