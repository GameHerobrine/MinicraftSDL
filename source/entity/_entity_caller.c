#include <entity/entity.h>
#include <entity/player.h>
#include <entity/itementity.h>
#include <entity/particle/smashparticle.h>
#include <entity/particle/textparticle.h>
#include <entity/inventory.h>

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
			//TODO furniture
		case SPARK:

		case SLIME:
		case ZOMBIE:
		case AIRWIZARD:
			//TODO MOB
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

void call_entity_touchItem(Entity* entity, ItemEntity* item){
	Player* pl;
	switch(entity->type){
		case PLAYER:
			pl = (Player*) entity;
			itementity_take(item, entity);
			inventory_addItem(&pl->inventory, &item->item);
			break;
		default:
			break;
	}
}
void call_entity_die(Entity* entity){
	switch(entity->type){
		case PLAYER:
			player_die(entity);
			break;
		case SLIME: //TODO SLIME
		case ZOMBIE: //TODO ZOMBIE
		case AIRWIZARD: //TODO AIRWIZARD
			mob_die(entity);
			break;
		default:
			printf("Tried dying undyable entity (wat)! %d\n", entity->type);
			break;
	}
}
void call_entity_doHurt(Entity* entity, int damage, int attackDir){
	switch(entity->type){
		case PLAYER:
			player_doHurt(entity, damage, attackDir);
			break;
		case SLIME:
		case ZOMBIE:
		case AIRWIZARD:
			mob_doHurt(entity, damage, attackDir);
			break;
		default:
			printf("Tried hurting unhurtable entity! %d\n", entity->type);
			break;
	}
}

void call_entity_touchedBy(Entity* entity, Entity* e){
	switch(entity->type){
		case AIRWIZARD:
			//TODO airwizard
			break;

		case ANVIL:
		case CHEST:
		case FURNACE:
		case LANTERN:
		case OVEN:
		case WORKBENCH:
			//TODO furniture
			break;
		case ITEMENTITY:
			if(((ItemEntity*)entity)->time > 30) call_entity_touchItem(e, entity);
			break;
		case PLAYER:
			if(e->type != PLAYER) call_entity_touchedBy(e, entity);
			break;
		case SLIME:
			//TODO Slime
			break;
		case ZOMBIE:
			//TODO Zombie
			break;
		default:
			break;
	}
}
char call_entity_blocks(Entity* entity, Entity* e){
	switch(entity->type){
		case ANVIL:
		case CHEST:
		case FURNACE:
		case LANTERN:
		case OVEN:
		case WORKBENCH:
			//TODO furniture
			break;
		case SLIME:
		case ZOMBIE:
		case AIRWIZARD:
		case PLAYER:
			//TODO MOB
			return call_entity_isBlockableBy(e, entity);
		default:
			return 0;
	}
}
void call_entity_free(Entity* entity){
	switch(entity->type){
		case TEXTPARTICLE:
			textparticle_free((TextParticle*) entity);
			break;
		case PLAYER:
			player_free((Player*) entity);
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
