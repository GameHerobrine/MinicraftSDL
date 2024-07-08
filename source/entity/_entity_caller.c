#include <entity/entity.h>
#include <entity/player.h>
#include <entity/particle/smashparticle.h>

void call_entity_tick(Entity* entity){
	switch(entity->type){
		case PLAYER:
			player_tick((Player*) entity);
			break;
		case SMASHPARTICLE:
			smashparticle_tick((SmashParticle*) entity);
			break;
		default:
			printf("Calling entity tick on unknown entity type! %d\n", entity->type);
			break;
	}
}

uint8_t call_entity_canSwim(Entity* entity){
	switch(entity->type){
		case PLAYER:
			return 1;
		default:
			printf("Calling entity canSwim on unknown type!");
		case SMASHPARTICLE:
			return 0;
	}
}

void call_entity_render(Entity* entity, Screen* screen){
	switch(entity->type){
		case PLAYER:
			player_render((Player*) entity, screen);
			break;
		case SMASHPARTICLE:
			smashparticle_render((SmashParticle*) entity, screen);
			break;
		default:
			printf("Calling entity render on unknown entity type! %d\n", entity->type);
			break;
	}
}
char call_entity_isSwimming(Entity* entity){
	switch(entity->type){
		case PLAYER:
			return mob_isSwimming((Mob*) entity);
		default:
			printf("Calling entity isSwimming on unknown entity type! %d\n", entity->type);
		case SMASHPARTICLE:
			return 0;
	}
}
