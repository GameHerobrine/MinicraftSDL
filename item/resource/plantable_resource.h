#ifndef ITEM_RESOURCE_PLANTABLE_RESOURCE_H_
#define ITEM_RESOURCE_PLANTABLE_RESOURCE_H_

#include "../../level/tile/tile.h"

struct _resource;

typedef struct{
	int sourceTilesSize;
	TileID* sourceTiles;
	TileID targetTile;
} res_plantable;



void init_plantable_resource(struct _resource* resource, char* name, int sprite, int color, TileID target, TileID* source, int size);

#endif /* ITEM_RESOURCE_PLANTABLE_RESOURCE_H_ */
