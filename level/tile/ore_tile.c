#include "tile.h"
#include "../../item/resource/resource.h"

void oretile_init(TileID id, Resource* toDrop){
	tile_init(id);
	Tile* t = tiles + id;
	t->add.ore.toDrop = toDrop;
	t->add.ore.color = toDrop->color & 0xffff00;
}

//TODO render: Level*
//TODO mayPass: Level*, Entity* -> return false;
//TODO hurt: Level*, Mob*
//TODO interact: Level*, PLayer*, Item*
//TODO custom hurt
//TODO bumpedInto -> Level*, Entity*
