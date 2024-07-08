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
uint8_t item_matches(Item* item, Item* item2){
	return item->id == item2->id;
}
