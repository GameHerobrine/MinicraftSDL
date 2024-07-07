#include <entity/entity.h>

void entity_create(Entity* entity){
	entity->x = entity->y = 0;
	entity->xr = entity->yr = 6;
	entity->removed = 0;
	random_set_seed(&entity->random, getTimeMS());
}

uint8_t entity_canSwim(Entity* entity){
	return 0;
}

int getLightRadius(Entity* entity){
	return 0;
}
