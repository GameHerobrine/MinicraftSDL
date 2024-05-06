#include "tile.h";

void stairstile_init(TileID id, char leadsUp){
	tile_init(id);
	tiles[id].additionalData = leadsUp;
}

//TODO override render
