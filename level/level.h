#ifndef LEVEL_LEVEL_H_
#define LEVEL_LEVEL_H_
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

void init_level(Level* lvl, int w, int h, int level, Level* parent);
unsigned char level_get_tile(Level* level, int x, int y);
unsigned char level_get_data(Level* level, int x, int y);


#endif /* LEVEL_LEVEL_H_ */
