#ifndef _ENTITY_CALLER_H
#define _ENTITY_CALLER_H
#include <entity/entity.h>
#include <entity/itementity.h>
#include <gfx/screen.h>

void call_entity_tick(Entity* entity);
void call_entity_render(Entity* entity, Screen* screen);
char call_entity_isSwimming(Entity* entity);
uint8_t call_entity_canSwim(Entity* entity);
void call_entity_free(Entity* entity);
void call_entity_touchedBy(Entity* entity, Entity* e);
char call_entity_blocks(Entity* entity, Entity* e);
void call_entity_touchItem(Entity* entity, ItemEntity* item);
void call_entity_die(Entity* mob);

#endif // _ENTITY_CALLER_H
