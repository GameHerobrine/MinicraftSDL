#include "tile.h"

void saplingtile_init(TileID id, TileID onType, TileID growsTo){
	tile_init(id);
	
	Tile* tile = tiles + id;
	tile->additionalData = onType;
	tile->additionalData2 = growsTo;
	
	Tile* on = tiles + onType;
	
	tile->connectsToSand = on->connectsToSand;
	tile->connectsToGrass = on->connectsToGrass;
	tile->connectsToWater = on->connectsToWater;
	tile->connectsToLava = on->connectsToLava;
}

//TODO override render, tick, hurt
