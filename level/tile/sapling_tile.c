#include "tile.h"

void saplingtile_init(TileID id, TileID onType, TileID growsTo){
	tile_init(id);
	
	Tile* tile = tiles + id;
	tile->add.sapling.onType = onType;
	tile->add.sapling.growsTo = growsTo;
	
	Tile* on = tiles + onType;
	
	tile->connectsToSand = on->connectsToSand;
	tile->connectsToGrass = on->connectsToGrass;
	tile->connectsToWater = on->connectsToWater;
	tile->connectsToLava = on->connectsToLava;
}

void saplingtile_render(TileID id, Screen* screen, Level* level, int x, int y){
	tile_render(tiles[id].add.sapling.onType, screen, level, x, y);
	int col = getColor4(10, 40, 50, -1);
	render_screen(screen, x * 16 + 4, y * 16 + 4, 11 + 3 * 32, col, 0);
}

//TODO override render, tick, hurt
