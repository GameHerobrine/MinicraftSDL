#include "tile.h"

void flowertile_init(TileID id){
	tile_init(id);
	tiles[id].connectsToGrass = 1;
}

//TODO override render, interact, hurt
