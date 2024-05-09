#ifndef LEVEL_TILE_CACTUS_TILE_H_
#define LEVEL_TILE_CACTUS_TILE_H_

#include "tile.h"

void cactustile_init(TileID id);
void cactustile_render(TileID id, Screen* screen, Level* level, int x, int y);

#endif /* LEVEL_TILE_CACTUS_TILE_H_ */
