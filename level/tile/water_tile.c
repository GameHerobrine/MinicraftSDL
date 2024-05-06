#include "tile.h"

void watertile_init(TileID id){
	tile_init(id);
	
	Tile* tile = tiles + id;
	tile->connectsToSand = 1;
	tile->connectsToWater = 1;
}

//TODO override: render, mayPass, tick. + add wRandom
