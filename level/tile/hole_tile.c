#include "tile.h"

void holetile_init(TileID id){
	tile_init(id);
	
	Tile* t = tiles + id;
	t->connectsToSand = 1;
	t->connectsToWater = 1;
	t->connectsToLava = 1;
}

//TODO override render, mayPass -> e->canSwim();
