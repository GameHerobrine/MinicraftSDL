#include "tile.h"

void grasstile_init(TileID id){
	tile_init(id);
	Tile* t = tiles + id;
	
	t->connectsToGrass = 1;
}

//TODO override render, tick, interact 
