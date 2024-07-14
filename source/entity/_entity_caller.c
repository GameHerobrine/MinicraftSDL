#include <entity/entity.h>
#include <entity/player.h>
#include <entity/itementity.h>
#include <entity/particle/smashparticle.h>
#include <entity/particle/textparticle.h>
#include <entity/inventory.h>
#include <entity/furniture.h>
#include <entity/workbench.h>
#include <entity/lantern.h>
#include <entity/slime.h>
#include <entity/zombie.h>
#include <entity/oven.h>
#include <entity/furnace.h>
#include <entity/anvil.h>
#include <entity/chest.h>

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
			furniture_tick((Furniture*)entity);
			break;
		case SLIME:
			slime_tick(entity);
			break;
		case ZOMBIE:
			zombie_tick(entity);
			break;
		case SPARK: //TODO spark
		case AIRWIZARD: //TODO airwizard
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
		case PLAYER:
		default:
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
		case SLIME:
			slime_render(entity, screen);
			break;
		case ZOMBIE:
			zombie_render(entity, screen);
			break;
		case ANVIL:
		case CHEST:
		case FURNACE:
		case LANTERN:
		case OVEN:
		case WORKBENCH:
			furniture_render(entity, screen);
			break;
		case AIRWIZARD: //TODO airwizard
		case SPARK: //TODO spark
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
		case SLIME:
			slime_die(entity);
			break;
		case ZOMBIE:
			zombie_die(entity);
			break;
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

void call_entity_hurtTile(Entity* entity, TileID tile, int x, int y, int damage){
	switch(entity->type){
		case SLIME:
		case ZOMBIE:
		case AIRWIZARD:
		case PLAYER:
			mob_hurtTile(entity, tile, x, y, damage);
			break;
	}
}

void call_entity_hurt(Entity* entity, Mob* mob, int damage, int attackDir){
	switch(entity->type){
		case SLIME:
		case ZOMBIE:
		case AIRWIZARD:
		case PLAYER:
			mob_hurt(entity, mob, damage, attackDir);
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
			furniture_touchedBy(entity, e);
			break;
		case ITEMENTITY:
			if(((ItemEntity*)entity)->time > 30) call_entity_touchItem(e, entity);
			break;
		case PLAYER:
			if(e->type != PLAYER) call_entity_touchedBy(e, entity);
			break;
		case SLIME:
			slime_touchedBy(entity, e);
			break;
		case ZOMBIE:
			zombie_touchedBy(entity, e);
			break;
		default:
			break;
	}
}

char call_entity_use(Entity* entity, Player* player, int attackDir){
	switch(entity->type){
		case ANVIL:
			return anvil_use(entity, player, attackDir);
		case CHEST:
			return chest_use(entity, player, attackDir);
		case FURNACE:
			return furnace_use(entity, player, attackDir);
		case OVEN:
			return oven_use(entity, player, attackDir);
		case WORKBENCH:
			return workbench_use(entity, player, attackDir);
		default:
			return 0;
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
			return 1;
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
char entity_ismob(Entity* entity){
	switch(entity->type){
		case SLIME:
		case ZOMBIE:
		case AIRWIZARD:
		case PLAYER:
			return 1;
		default:
			return 0;
	}
}

Furniture* entity_createFurniture(EntityId id){
	Furniture* furn = 0;
	switch(id){
		case ANVIL:
			furn = malloc(sizeof(Anvil));
			anvil_create(furn);
			break;
		case CHEST:
			furn = malloc(sizeof(Chest));
			chest_create(furn);
			break;
		case FURNACE:
			furn = malloc(sizeof(Furnace));
			furnace_create(furn);
			break;
		case LANTERN:
			furn = malloc(sizeof(Lantern));
			lantern_create(furn);
			break;
		case OVEN:
			furn = malloc(sizeof(Oven));
			oven_create(furn);
			break;
		case WORKBENCH:
			furn = malloc(sizeof(Workbench));
			workbench_create(furn);
			break;
	}

	return furn;
}

char entity_isfurniture(Entity* entity){
	switch(entity->type){
		case ANVIL:
		case CHEST:
		case FURNACE:
		case LANTERN:
		case OVEN:
		case WORKBENCH:
			return 1;
		default:
			return 0;
	}
}
int call_entity_getLightRadius(Entity* entity){
	int r, rr;
	Player* p;
	switch(entity->type){
		case LANTERN:
			return 8;
		case PLAYER:
			r = 2;
			p = (Player*) entity;
			if(p->activeItem && p->activeItem->id == FURNITURE){
				rr = call_entity_getLightRadius(p->activeItem->add.furniture.furniture);
				if(rr > r) return rr;
			}
			return r;
		default:
			return 0;
	}
}
Furniture* furniture_create_copy(Furniture* old){
	size_t size;
	switch(old->entity.type){
		case WORKBENCH:
			size = sizeof(Workbench);
			break;
		case LANTERN:
			size = sizeof(Lantern);
			break;
		case OVEN:
			size = sizeof(Oven);
			break;
		case FURNACE:
			size = sizeof(Furnace);
			break;
		case ANVIL:
			size = sizeof(Anvil);
			break;
		case CHEST:
			size = sizeof(Chest);
			break;
		default:
			return 0;
	}

	Furniture* new = malloc(size);
	memcpy(new, old, size);
	old->name = 0;
	return new;
}

void call_entity_free(Entity* entity){
	switch(entity->type){
		case TEXTPARTICLE:
			textparticle_free((TextParticle*) entity);
			break;
		case CHEST:
			chest_free(entity);
			break;
		case ANVIL:
		case FURNACE:
		case LANTERN:
		case OVEN:
		case WORKBENCH:
			furniture_free(entity);
			break;
		case PLAYER:
			player_free((Player*) entity);
	}
}

char call_entity_isSwimming(Entity* entity){
	switch(entity->type){
		case PLAYER:
		case SLIME:
		case ZOMBIE:
		case AIRWIZARD:
			return mob_isSwimming((Mob*) entity);
		default:
			printf("Calling entity isSwimming on unknown entity type! %d\n", entity->type);
		case SMASHPARTICLE:
			return 0;
	}
}
