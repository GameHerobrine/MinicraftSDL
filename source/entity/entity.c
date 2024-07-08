#include <entity/entity.h>
#include <level/tile/tileids.h>
#include <level/tile/tile.h>

void entity_create(Entity* entity){
	entity->x = entity->y = 0;
	entity->xr = entity->yr = 6;
	entity->removed = 0;
	random_set_seed(&entity->random, getTimeMS());
}

uint8_t entity_canSwim(Entity* entity){
	return 0;
}
void entity_render(Entity* entity, Screen* screen){
	//useless
}

void entity_remove(Entity* entity){
	entity->removed = 1;
}

int entity_getLightRadius(Entity* entity){
	return 0;
}

void entity_init(Entity* entity, Level* level){
	entity->level = level;
}

uint8_t entity_move2(Entity* entity, int xa, int ya){
	if(xa && ya){
		printf("Entity(%d) called move2 with xa and ya != 0!\n");
	}

	int xto0 = (entity->x - entity->xr) >> 4;
	int yto0 = (entity->y - entity->yr) >> 4;
	int xto1 = (entity->x + entity->xr) >> 4;
	int yto1 = (entity->y + entity->yr) >> 4;

	int xt0 = (entity->x + xa - entity->xr) >> 4;
	int yt0 = (entity->y + ya - entity->yr) >> 4;
	int xt1 = (entity->x + xa + entity->xr) >> 4;
	int yt1 = (entity->y + ya + entity->yr) >> 4;

	uint8_t blocked = 0;
	for(int yt = yt0; yt <= yt1; ++yt){
		for(int xt = xt0; xt <= xt1; ++xt){
			if(xt >= xto0 && xt <= xto1 && yt >= yto0 && yt <= yto1) continue;

			TileID tile = level_get_tile(entity->level, xt, yt);
			//TODO tile_bumpedInto
			tile = level_get_tile(entity->level, xt, yt); //reget tile in case bumpedInto changed it?
			if(!tile_mayPass(tile, entity->level, xt, yt, entity)){
				blocked = 1; //not needed?
				return 0;
			}
		}
	}

	if(blocked) return 0;

	/* TODO entity collisions?
	 * List<Entity> wasInside = level.getEntities(x - xr, y - yr, x + xr, y + yr);
		List<Entity> isInside = level.getEntities(x + xa - xr, y + ya - yr, x + xa + xr, y + ya + yr);
		for (int i = 0; i < isInside.size(); i++) {
			Entity e = isInside.get(i);
			if (e == this) continue;

			e.touchedBy(this);
		}
		isInside.removeAll(wasInside);
		for (int i = 0; i < isInside.size(); i++) {
			Entity e = isInside.get(i);
			if (e == this) continue;

			if (e.blocks(this)) {
				return false;
			}
		}
	*/
	entity->x += xa;
	entity->y += ya;

	return 1;
}
uint8_t entity_move(Entity* entity, int xa, int ya){
	if(xa || ya){
		uint8_t stopped = 1;

		if(xa != 0 && entity_move2(entity, xa, 0)) stopped = 0;
		if(ya != 0 && entity_move2(entity, 0, ya)) stopped = 0;

		if(!stopped){
			int xt = entity->x >> 4;
			int yt = entity->y >> 4;

			uint8_t tile = level_get_tile(entity->level, xt, yt);
			//TODO tile_steppedOn()
		}
		return !stopped;
	}
	return 1;
}
