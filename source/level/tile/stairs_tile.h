
#ifndef LEVEL_TILE_STAIRS_TILE_H_
#define LEVEL_TILE_STAIRS_TILE_H_

enum tileid_;
typedef struct{
	char leadsUp;
} add_stairs_;

void stairstile_init(enum tileid_ id, char leadsUp);

#endif /* LEVEL_TILE_STAIRS_TILE_H_ */
