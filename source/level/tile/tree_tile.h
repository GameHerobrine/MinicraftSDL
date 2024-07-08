#ifndef LEVEL_TILE_TREE_TILE_H_
#define LEVEL_TILE_TREE_TILE_H_
#include "tile.h"

void treetile_init(TileID id);
void treetile_tick(TileID id, Level* level, int xt, int yt);
void treetile_hurt(TileID id, Level* level, int x, int y, Mob* source, int dmg, int attackDir);

#endif /* LEVEL_TILE_TREE_TILE_H_ */
