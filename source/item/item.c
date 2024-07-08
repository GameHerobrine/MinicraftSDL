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
