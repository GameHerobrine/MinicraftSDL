#include "tile.h"

void cactustile_init(TileID id){
	tile_init(id);
	tiles[id].connectsToSand = 1;
}

//TODO override render, mayPass -> false, hurt, bumpedInto, tick
