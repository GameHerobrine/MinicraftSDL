#ifndef LEVEL_TILE_SAPLING_TILE_H_
#define LEVEL_TILE_SAPLING_TILE_H_
#include "tileids.h"

typedef struct{
	TileID onType;
	TileID growsTo;
} add_sapling_;

void saplingtile_init(TileID id, TileID onType, TileID growsTo);

#endif /* LEVEL_TILE_SAPLING_TILE_H_ */
