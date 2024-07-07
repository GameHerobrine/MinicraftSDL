#ifndef ENTITY_H
#define ENTITY_H
#include <utils/javarandom.h>
#include <utils/utils.h>
#include <level/level.h>
#include <stdint.h>

typedef struct{
	Random random;
	int x, y;
	int xr, yr;
	Level* level;
	uint8_t removed;
} Entity;

struct _Mob;

void entity_create(Entity* entity);
void entity_tick(Entity* entity);
void entity_render(Entity* entity, Screen* screen);
void entity_remove(Entity* entity);
void entity_init(Entity* entity, Level* level);
uint8_t entity_intersects(Entity* entity, int x0, int y0, int x1, int y1);
uint8_t entity_blocks(Entity* entity, Entity* other);
//TODO hurt
//TODO hurt
//TODO move
//TODO move2
//TODO touchedBy
//TODO isBlockableBy
//TODO TouchItem
uint8_t entity_canSwim(Entity* entity);
//TODO interact
//TODO use
int getLightRadius(Entity* entity);



#endif // ENTITY_H
