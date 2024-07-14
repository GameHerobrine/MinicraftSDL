#include <entity/chest.h>
#include <entity/player.h>
#include <entity/inventory.h>

void chest_create(Chest* chest){
	char* name = malloc(strlen("Chest")+1); //XXX ew
	strcpy(name, "Chest");
	furniture_create(chest, name);
	chest->furniture.entity.type = CHEST;
	chest->furniture.col = getColor4(-1, 110, 331, 552);
	chest->furniture.sprite = 1;

	inventory_create(&chest->inventory);
}

char chest_use(Chest* chest, struct _Player* player, int attackDir){
	//player.game.setMenu(new ContainerMenu(player, "Chest", inventory));
	//TODO container menu
	return 1;
}

void chest_free(Chest* chest){
	furniture_free(chest);
	inventory_free(&chest->inventory);
}
