#include <entity/entity.h>
#include <entity/player.h>
#include <entity/itementity.h>
#include <entity/particle/smashparticle.h>
#include <entity/particle/textparticle.h>

void call_entity_tick(Entity* entity){
	switch(entity->type){
		case PLAYER:
			player_tick((Player*) entity);
			break;
		case SMASHPARTICLE:
			smashparticle_tick((SmashParticle*) entity);
			break;
		case TEXTPARTICLE:
			textparticle_tick((TextParticle*) entity);
			break;
		case ITEMENTITY:
			itementity_tick((ItemEntity*) entity);
			break;
		case ANVIL:
		case CHEST:
		case FURNACE:
		case LANTERN:
		case OVEN:
		case WORKBENCH:

		case SPARK:
		case SLIME:
		case ZOMBIE:
		case AIRWIZARD:
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
			return 0;
	}
}

uint8_t call_entity_isBlockableBy(Entity* entity, Mob* mob){
	switch(entity->type){
		case ITEMENTITY:
		case SPARK:
			return 0;
		default:
			printf("failed isBlockableBy\n");
		case PLAYER:
			return 1;
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
		case ITEMENTITY:
			itementity_render((ItemEntity*) entity, screen);
			break;
		case TEXTPARTICLE:
			textparticle_render((TextParticle*) entity, screen);
			break;
		default:
			printf("Calling entity render on unknown entity type! %d\n", entity->type);
			break;
	}
}

void call_entity_free(Entity* entity){
	switch(entity->type){
		case TEXTPARTICLE:
			textparticle_free((TextParticle*) entity);
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
