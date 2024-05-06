#include "tile.h"

void treetile_init(TileID id){
	tile_init(id);
	tiles[id].connectsToGrass = 1;
}

//TODO override: render, tick, mayPass -> false, hurt, interact + private hurt(Level*, x, y, int dmg);

