#include "tile.h"

void lavatile_init(TileID id){
	tile_init(id);
	
	Tile* tile = tiles + id;
	tile->connectsToSand = tile->connectsToLava = 1;
}

//TODO wRandom
//TODO override render, mayPass, tick, getlightRadius -> 6
