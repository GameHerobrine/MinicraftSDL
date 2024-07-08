#include <entity/mob.h>
#include <entity/entity.h>
#include <level/tile/tileids.h>
#include <entity/_entity_caller.h>

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

void mob_tick(Mob* mob){
	++mob->tickTime;
	if(level_get_tile(mob->entity.level, mob->entity.x >> 4, mob->entity.y >> 4) == LAVA){
		//TODO hurt(this, 4, dir ^ 1);
	}
	if(mob->health <= 0){
		//TODO kys (die());
	}

	if(mob->hurtTime > 0) --mob->hurtTime;

}
uint8_t mob_isSwimming(Mob* mob){
	TileID tile = level_get_tile(mob->entity.level, mob->entity.x >> 4, mob->entity.y >> 4);
	return tile == WATER || tile == LAVA;
}
uint8_t mob_move(Mob* mob, int xa, int ya){
	if(call_entity_isSwimming(&mob->entity)){
		if(mob->swimTimer++ % 2 == 0) return 1;
	}

	if(mob->xKnockback < 0){
		entity_move2(&mob->entity, -1, 0);
		++mob->xKnockback;
	}

	if(mob->xKnockback > 0){
		entity_move2(&mob->entity, 1, 0);
		--mob->xKnockback;
	}

	if(mob->yKnockback < 0){
		entity_move2(&mob->entity, 0, -1);
		++mob->yKnockback;
	}

	if(mob->yKnockback < 0){
		entity_move2(&mob->entity, 0, 1);
		--mob->yKnockback;
	}

	if(mob->hurtTime > 0) return 1;

	if(xa != 0 || ya != 0){
		++mob->walkDist;
		if(xa < 0) mob->dir = 2;
		if(xa > 0) mob->dir = 3;
		if(ya < 0) mob->dir = 1;
		if(ya > 0) mob->dir = 0;
	}

	entity_move(&mob->entity, xa, ya);
}
