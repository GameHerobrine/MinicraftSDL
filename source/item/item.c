#include "item.h"
#include "powergloveitem.h"
#include "resourceitem.h"

int item_getColor(Item* item){
	switch(item->id){
		case POWERGLOVE:
			return powergloveitem_getColor(item);
		case RESOURCE:
			return resourceitem_getColor(item);
		//TODO case TOOLITEM:
		//TODO case FURNITURE:
		default:
			return 0;
	}
}
int item_getSprite(Item* item){
	switch(item->id){
		case POWERGLOVE:
			return powergloveitem_getSprite(item);
		case RESOURCE:
			return resourceitem_getSprite(item);
		//TODO case TOOLITEM:
		//TODO case FURNITURE:
		default:
			return 0;
	}
}
void item_renderIcon(Item* item, Screen* screen, int x, int y){
	switch(item->id){
		case POWERGLOVE:
			powergloveitem_renderIcon(item, screen, x, y);
			break;
		case RESOURCE:
			resourceitem_renderIcon(item, screen, x, y);
			break;
		//TODO case TOOLITEM:
		//TODO case FURNITURE:
		default:
			break;
	}
}
uint8_t item_interactOn(Item* item, TileID tile, Level* level, int xt, int yt, struct _Player* player, int attackDir){
	switch(item->id){
		case FURNITURE:
			//TODO furniture
			return 0;
		case RESOURCE:
			return resourceitem_interactOn(item, tile, level, xt, yt, player, attackDir);
		default:
			return 0;
	}
}

void item_renderInventory(Item* item, Screen* screen, int x, int y){
	switch(item->id){
		case POWERGLOVE:
			powergloveitem_renderInventory(item, screen, x, y);
			break;
		case RESOURCE:
			resourceitem_renderInventory(item, screen, x, y);
			break;
		//TODO case TOOLITEM:
		//TODO case FURNITURE:
		default:
			break;
	}
}

uint8_t item_isDepleted(Item* item){
	switch(item->id){
		case RESOURCE:
			return item->add.resource.count <= 0;
		//TODO case FURNITURE: return item.add.furniture.placed;
		default:
			return 0;
	}
}

void item_onTake(Item* item, struct _ItemEntity* itemEntity){
	//does nothing even in overrides
}

uint8_t item_canAttack(Item* item){
	switch(item->id){
		case TOOL:
			return 1;
		case FURNITURE:
			return 0;
		default:
			return 0;
	}
}

int item_getAttackDamageBonus(Item* item, Entity* entity);
char* item_getName(Item* item);
uint8_t matches(Item* item, Item* item2);

uint8_t item_matches(Item* item, Item* item2){
	return item->id == item2->id;
}
