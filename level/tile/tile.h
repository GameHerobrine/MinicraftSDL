#ifndef LEVEL_TILE_TILE_H_
#define LEVEL_TILE_TILE_H_

#include "../../utils/javarandom.h"

typedef enum{
	GRASS,
	ROCK,
	WATER,
	FLOWER,
	TREE,
	DIRT,
	SAND,
	CACTUS,
	HOLE,
	TREE_SAPLING,
	CACTUS_SAPLING,
	FARMLAND,
	WHEAT,
	LAVA,
	STAIRS_DOWN,
	STAIRS_UP,
	INFINITE_FALL,
	CLOUD,
	HARD_ROCK,
	IRON_ORE,
	GOLD_ORE,
	GEM_ORE,
	CLOUD_CACTUS
} TileID;

typedef struct{
	Random random;
	
	TileID id;
	
	int additionalData; //added to not use mallocs/frees
	int additionalData2;
	
	char connectsToGrass : 1;
	char connectsToSand : 1;
	char connectsToLava : 1;
	char connectsToWater : 1;
} Tile;

extern Tile tiles[256];

void init_tiles();
void tile_init(TileID id);

#endif /* LEVEL_TILE_TILE_H_ */
