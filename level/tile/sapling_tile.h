#ifndef LEVEL_TILE_SAPLING_TILE_H_
#define LEVEL_TILE_SAPLING_TILE_H_
#include "tileids.h"
#include "../level.h"
#include "../../gfx/screen.h"
typedef struct{
	TileID onType;
	TileID growsTo;
} add_sapling_;

void saplingtile_init(TileID id, TileID onType, TileID growsTo);
void saplingtile_render(TileID id, Screen* screen, Level* level, int x, int y); 

#endif /* LEVEL_TILE_SAPLING_TILE_H_ */
