#ifndef LEVEL_TILE_FLOWER_TILE_H_
#define LEVEL_TILE_FLOWER_TILE_H_
#include "tile.h"

void flowertile_init(TileID id);
void flowertile_hurt(TileID id, Level* level, int x, int y, Mob* source, int dmg, int attackDir);

#endif /* LEVEL_TILE_FLOWER_TILE_H_ */
