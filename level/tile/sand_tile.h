#ifndef LEVEL_TILE_SAND_TILE_H_
#define LEVEL_TILE_SAND_TILE_H_
#include "tile.h"

void sandtile_init(TileID id);
void sandtile_render(TileID id, Screen* screen, Level* level, int x, int y);

#endif /* LEVEL_TILE_SAND_TILE_H_ */
