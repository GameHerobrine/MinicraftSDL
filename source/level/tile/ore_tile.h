#ifndef LEVEL_TILE_ORE_TILE_H_
#define LEVEL_TILE_ORE_TILE_H_
#include "tileids.h"
#include "../level.h"
#include "../../gfx/screen.h"
struct _Resource;

typedef struct{
	struct _Resource* toDrop;
	int color;
} add_ore_;

void oretile_init(TileID id, struct _Resource* toDrop);
void oretile_render(TileID id, Screen* screen, Level* level, int x, int y);

#endif /* LEVEL_TILE_ORE_TILE_H_ */
