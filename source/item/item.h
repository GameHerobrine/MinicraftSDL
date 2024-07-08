#ifndef ITEM_H
#define ITEM_H
#include <utils/javarandom.h>
#include <gfx/screen.h>
#include <stdint.h>
#include <entity/entity.h>
#include <level/tile/tileids.h>
#include <level/level.h>
#include "itemids.h"
#include <item/resource/resource.h>
#include <entity/player.h>

typedef struct _Item{
	ItemID id;
	union{
		struct{
			Resource* resource;
			int count;
		} resource;
	} add;
} Item;
struct _Player;

int item_getColor(Item* item);
int item_getSprite(Item* item);
//TODO void item_onTake(Item* item, ItemEntity* itemEntity);
void item_renderInventory(Item* item, Screen* screen, int x, int y);
uint8_t item_interact(Item* item, struct _Player* player, Entity* entity, int attackDir);
void item_renderIcon(Item* item, Screen* screen, int x, int y);
uint8_t item_interactOn(Item* item, TileID tile, Level* level, int xt, int yt, struct _Player* player, int attackDir);
uint8_t item_isDepleted(Item* item);
uint8_t item_canAttack(Item* item);
int item_getAttackDamageBonus(Item* item, Entity* entity);
char* item_getName(Item* item);
uint8_t matches(Item* item, Item* item2);


#endif // ITEM_H
