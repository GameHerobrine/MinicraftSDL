#include <entity/mob.h>
#include <entity/entity.h>
#include <level/tile/tileids.h>
#include <entity/_entity_caller.h>
#include <game.h>
#include <entity/particle/textparticle.h>

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
void mob_doHurt(Mob* mob, int damage, int attackDir){
	if(mob->hurtTime > 0) return;

	if(game_player->mob.entity.level == mob->entity.level){
		/*TODO: Sounds
		 * int xd = level.player.x - x;
			int yd = level.player.y - y;
			if (xd * xd + yd * yd < 80 * 80) {
				Sound.monsterHurt.play();
			}
		*/
	}

	TextParticle* txt = malloc(sizeof(TextParticle));
	char* tx_ = malloc(16);
	sprintf(tx_, "%d\00", damage);
	textparticle_create(txt, tx_, mob->entity.x, mob->entity.y, getColor4(-1, 500, 500, 500));
	level_addEntity(mob->entity.level, txt);
	mob->health -= damage;
	if(attackDir == 0) mob->yKnockback = 6;
	if(attackDir == 1) mob->yKnockback = -6;
	if(attackDir == 2) mob->xKnockback = -6;
	if(attackDir == 3) mob->xKnockback = 6;
	mob->hurtTime = 10;
}
void mob_hurt(Mob* mob, int damage, int attackDir){
	call_entity_doHurt(mob, damage, attackDir);
}

void mob_die(Mob* mob){
	entity_remove(mob);
}

void mob_tick(Mob* mob){
	++mob->tickTime;
	if(level_get_tile(mob->entity.level, mob->entity.x >> 4, mob->entity.y >> 4) == LAVA){
		mob_hurt(mob, 4, mob->dir ^ 1);
	}
	if(mob->health <= 0){
		call_entity_die(mob);
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

	if(mob->yKnockback > 0){
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

	return entity_move(&mob->entity, xa, ya);
}
