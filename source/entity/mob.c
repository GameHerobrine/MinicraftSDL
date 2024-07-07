#include <entity/mob.h>
#include <entity/entity.h>

void mob_create(Mob* mob){
	entity_create(&mob->entity);
	mob->walkDist = mob->dir = mob->hurtTime = 0;
	mob->xKnockback = mob->yKnockback = 0;
	mob->maxHealth = 10;
	mob->health = mob->maxHealth;
	mob->swimTimer = mob->tickTime = 0;

	mob->entity.x = mob->entity.y = 8;
	mob->entity.xr = 4;
	mob->entity.yr = 3;
}
