#include "tile.h"

void sandtile_init(TileID id){
	tile_init(id);
	tiles[id].connectsToSand = 1;
}

//TODO override render, tick, steppedOn(entity instance of Mob -> level.setData(x, y, 10)), interact
