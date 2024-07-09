#include <entity/workbench.h>
void workbench_create(Workbench* workbench){
	char* name = malloc(strlen("Workbench")+1); //XXX ew
	strcpy(name, "Workbench");
	furniture_create(workbench, name);
	workbench->entity.type = WORKBENCH;
	workbench->col = getColor4(-1, 100, 321, 431);
	workbench->sprite = 4;
	workbench->entity.xr = 3;
	workbench->entity.yr = 2;
}

char workbench_use(Workbench* workbench, struct _Player* player, int attackDir){
	//TODO: player.game.setMenu(new CraftingMenu(Crafting.workbenchRecipes, player));
	return 1;
}
