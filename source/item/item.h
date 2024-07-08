#ifndef ITEM_H
#define ITEM_H
#include <utils/javarandom.h>
#include <gfx/screen.h>
#include <stdint.h>
#include <entity/entity.h>
#include <entity/player.h>
#include <level/tile/tileids.h>
#include <level/level.h>
#include "itemids.h"

typedef struct{
	ItemID id;
} Item;

int item_getColor(Item* item);
int item_getSprite(Item* item);
//TODO void item_onTake(Item* item, ItemEntity* itemEntity);
void item_renderInventory(Item* item, Screen* screen, int x, int y);
uint8_t item_interact(Item* item, Player* player, Entity* entity, int attackDir);
void item_renderIcon(Item* item, Screen* screen, int x, int y);
uint8_t item_interactOn(Item* item, TileID tile, Level* level, int xt, int yt, Player* player, int attackDir);
uint8_t item_isDepleted(Item* item);
uint8_t item_canAttack(Item* item);
int item_getAttackDamageBonus(Item* item, Entity* entity);
char* item_getName(Item* item);
uint8_t matches(Item* item, Item* item2);


#endif // ITEM_H
