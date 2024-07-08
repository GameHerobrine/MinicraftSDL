#include <entity/entity.h>
#include <entity/player.h>

void call_entity_tick(Entity* entity){
	switch(entity->type){
		case PLAYER:
			player_tick((Player*) entity);
			break;
		default:
			printf("Calling entity tick on unknown entity type! %d\n", entity->type);
			break;
	}
}
void call_entity_render(Entity* entity, Screen* screen){
	switch(entity->type){
		case PLAYER:
			player_render((Player*) entity, screen);
			break;
		default:
			printf("Calling entity render on unknown entity type! %d\n", entity->type);
			break;
	}
}
char call_entity_isSwimming(Entity* entity){
	//TODO
	return 0;
}
