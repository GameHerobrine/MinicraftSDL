#ifndef _ENTITY_CALLER_H
#define _ENTITY_CALLER_H
#include <entity/entity.h>
#include <gfx/screen.h>

void call_entity_tick(Entity* entity);
void call_entity_render(Entity* entity, Screen* screen);
char call_entity_isSwimming(Entity* entity);
uint8_t call_entity_canSwim(Entity* entity);
void call_entity_free(Entity* entity);

#endif // _ENTITY_CALLER_H
