#ifndef LEVEL_TILE_ORE_TILE_H_
#define LEVEL_TILE_ORE_TILE_H_

struct _resource;

typedef struct{
	struct _resource* toDrop;
	int color;
} add_ore_;

void oretile_init(TileID id, struct _resource* toDrop);

#endif /* LEVEL_TILE_ORE_TILE_H_ */
