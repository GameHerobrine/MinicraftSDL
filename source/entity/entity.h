#ifndef ENTITY_H
#define ENTITY_H
#include <utils/javarandom.h>
#include <utils/utils.h>
#include <stdint.h>
#include <entity/entityid.h>
#include <gfx/screen.h>

struct level_;

typedef struct{
	EntityId type;
	Random random;
	int x, y;
	int xr, yr;
	struct level_* level;
	uint8_t removed;
} Entity;

struct _Mob;

void entity_create(Entity* entity);
void entity_tick(Entity* entity);
void entity_render(Entity* entity, Screen* screen);
void entity_remove(Entity* entity);
void entity_init(Entity* entity, struct level_* level);
uint8_t entity_intersects(Entity* entity, int x0, int y0, int x1, int y1);
uint8_t entity_blocks(Entity* entity, Entity* other);
//TODO hurt
//TODO hurt
uint8_t entity_move(Entity* entity, int xa, int ya);
uint8_t entity_move2(Entity* entity, int xa, int ya);
//TODO touchedBy
//TODO isBlockableBy
//TODO TouchItem
uint8_t entity_canSwim(Entity* entity);
//TODO interact
//TODO use
int entity_getLightRadius(Entity* entity);



#endif // ENTITY_H