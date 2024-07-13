#include <crafting/crafting.h>
#include <utils/arraylist.h>
#include <crafting/recipe.h>

ArrayList anvilRecipes = {0};
ArrayList ovenRecipes = {0};
ArrayList furnaceRecipes = {0};
ArrayList workbenchRecipes = {0};

void crafting_init(){
	create_arraylist(&anvilRecipes);
	create_arraylist(&ovenRecipes);
	create_arraylist(&furnaceRecipes);
	create_arraylist(&workbenchRecipes);

	Recipe* recipe = malloc(sizeof(Recipe));
	furniturerecipe_create(recipe, LANTERN);
	recipe_addCost(recipe, &wood, 5);
	recipe_addCost(recipe, &slime, 10);
	recipe_addCost(recipe, &glass, 4);
	arraylist_push(&workbenchRecipes, recipe);
	//TODO oven, furnace
	recipe = malloc(sizeof(Recipe));
	furniturerecipe_create(recipe, WORKBENCH);
	recipe_addCost(recipe, &wood, 20);
	arraylist_push(&workbenchRecipes, recipe);
	//TODO chest, anvil

	/* TODO:
	 * workbenchRecipes.add(new FurnitureRecipe(Lantern.class).addCost(Resource.wood, 5).addCost(Resource.slime, 10).addCost(Resource.glass, 4));

			workbenchRecipes.add(new FurnitureRecipe(Oven.class).addCost(Resource.stone, 15));
			workbenchRecipes.add(new FurnitureRecipe(Furnace.class).addCost(Resource.stone, 20));
			workbenchRecipes.add(new FurnitureRecipe(Workbench.class).addCost(Resource.wood, 20));
			workbenchRecipes.add(new FurnitureRecipe(Chest.class).addCost(Resource.wood, 20));
			workbenchRecipes.add(new FurnitureRecipe(Anvil.class).addCost(Resource.ironIngot, 5));

			workbenchRecipes.add(new ToolRecipe(ToolType.sword, 0).addCost(Resource.wood, 5));
			workbenchRecipes.add(new ToolRecipe(ToolType.axe, 0).addCost(Resource.wood, 5));
			workbenchRecipes.add(new ToolRecipe(ToolType.hoe, 0).addCost(Resource.wood, 5));
			workbenchRecipes.add(new ToolRecipe(ToolType.pickaxe, 0).addCost(Resource.wood, 5));
			workbenchRecipes.add(new ToolRecipe(ToolType.shovel, 0).addCost(Resource.wood, 5));
			workbenchRecipes.add(new ToolRecipe(ToolType.sword, 1).addCost(Resource.wood, 5).addCost(Resource.stone, 5));
			workbenchRecipes.add(new ToolRecipe(ToolType.axe, 1).addCost(Resource.wood, 5).addCost(Resource.stone, 5));
			workbenchRecipes.add(new ToolRecipe(ToolType.hoe, 1).addCost(Resource.wood, 5).addCost(Resource.stone, 5));
			workbenchRecipes.add(new ToolRecipe(ToolType.pickaxe, 1).addCost(Resource.wood, 5).addCost(Resource.stone, 5));
			workbenchRecipes.add(new ToolRecipe(ToolType.shovel, 1).addCost(Resource.wood, 5).addCost(Resource.stone, 5));

			anvilRecipes.add(new ToolRecipe(ToolType.sword, 2).addCost(Resource.wood, 5).addCost(Resource.ironIngot, 5));
			anvilRecipes.add(new ToolRecipe(ToolType.axe, 2).addCost(Resource.wood, 5).addCost(Resource.ironIngot, 5));
			anvilRecipes.add(new ToolRecipe(ToolType.hoe, 2).addCost(Resource.wood, 5).addCost(Resource.ironIngot, 5));
			anvilRecipes.add(new ToolRecipe(ToolType.pickaxe, 2).addCost(Resource.wood, 5).addCost(Resource.ironIngot, 5));
			anvilRecipes.add(new ToolRecipe(ToolType.shovel, 2).addCost(Resource.wood, 5).addCost(Resource.ironIngot, 5));

			anvilRecipes.add(new ToolRecipe(ToolType.sword, 3).addCost(Resource.wood, 5).addCost(Resource.goldIngot, 5));
			anvilRecipes.add(new ToolRecipe(ToolType.axe, 3).addCost(Resource.wood, 5).addCost(Resource.goldIngot, 5));
			anvilRecipes.add(new ToolRecipe(ToolType.hoe, 3).addCost(Resource.wood, 5).addCost(Resource.goldIngot, 5));
			anvilRecipes.add(new ToolRecipe(ToolType.pickaxe, 3).addCost(Resource.wood, 5).addCost(Resource.goldIngot, 5));
			anvilRecipes.add(new ToolRecipe(ToolType.shovel, 3).addCost(Resource.wood, 5).addCost(Resource.goldIngot, 5));

			anvilRecipes.add(new ToolRecipe(ToolType.sword, 4).addCost(Resource.wood, 5).addCost(Resource.gem, 50));
			anvilRecipes.add(new ToolRecipe(ToolType.axe, 4).addCost(Resource.wood, 5).addCost(Resource.gem, 50));
			anvilRecipes.add(new ToolRecipe(ToolType.hoe, 4).addCost(Resource.wood, 5).addCost(Resource.gem, 50));
			anvilRecipes.add(new ToolRecipe(ToolType.pickaxe, 4).addCost(Resource.wood, 5).addCost(Resource.gem, 50));
			anvilRecipes.add(new ToolRecipe(ToolType.shovel, 4).addCost(Resource.wood, 5).addCost(Resource.gem, 50));

			furnaceRecipes.add(new ResourceRecipe(Resource.ironIngot).addCost(Resource.ironOre, 4).addCost(Resource.coal, 1));
			furnaceRecipes.add(new ResourceRecipe(Resource.goldIngot).addCost(Resource.goldOre, 4).addCost(Resource.coal, 1));
			furnaceRecipes.add(new ResourceRecipe(Resource.glass).addCost(Resource.sand, 4).addCost(Resource.coal, 1));

			ovenRecipes.add(new ResourceRecipe(Resource.bread).addCost(Resource.wheat, 4));
			*/
}
void crafting_free(){
	for(int i = 0; i < anvilRecipes.size; ++i){
		recipe_free(anvilRecipes.elements[i]);
		free(anvilRecipes.elements[i]);
	}
	arraylist_remove(&anvilRecipes);

	for(int i = 0; i < ovenRecipes.size; ++i){
		recipe_free(ovenRecipes.elements[i]);
		free(ovenRecipes.elements[i]);
	}
	arraylist_remove(&ovenRecipes);

	for(int i = 0; i < furnaceRecipes.size; ++i){
		recipe_free(furnaceRecipes.elements[i]);
		free(furnaceRecipes.elements[i]);
	}
	arraylist_remove(&furnaceRecipes);

	for(int i = 0; i < workbenchRecipes.size; ++i){
		recipe_free(workbenchRecipes.elements[i]);
		free(workbenchRecipes.elements[i]);
	}
	arraylist_remove(&workbenchRecipes);



}
