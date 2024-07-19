cmake_minimum_required(VERSION 3.5)
project(minicraft-sdl LANGUAGES C)

add_compile_options(-Wno-implicit-function-declaration) #TODO delete this
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDLmain -lSDL -lm")

add_definitions(-DTEST_INVENTORY -DTEST_SHOWPORTALPOS -DGODMODE)

file(GLOB_RECURSE SOURCES *.c)
file(GLOB_RECURSE HEADERS *.h)

add_executable(minicraft-sdl ${SOURCES} ${HEADERS}
	entity/player.c
	entity/player.h
	entity/_entity_caller.c
	entity/_entity_caller.h
	entity/entityid.h
	item/itemids.h
	item/tooltype.h
	item/tooltype.c
	item/item.h
	entity/particle/smashparticle.c
	entity/particle/smashparticle.h
	item/item.c
	item/powergloveitem.c
	item/powergloveitem.h
	item/resourceitem.c
	item/resourceitem.h
	entity/itementity.h
	entity/itementity.c
	entity/particle/textparticle.c
	entity/particle/textparticle.h
	entity/inventory.h
	entity/inventory.c

	screen/inventorymenu.c
	screen/inventory_menu.h
	screen/dead_menu.c
	screen/dead_menu.h
	entity/furniture.h
	entity/furniture.c
	item/furniture_item.h
	item/furniture_item.c
	entity/workbench.h
	entity/workbench.c
	item/tool_item.h
	item/tool_item.c
	screen/level_transition_menu.h
	screen/level_transition_menu.c
	entity/lantern.h
	entity/lantern.c
	entity/slime.h
	entity/slime.c
	entity/zombie.h
	entity/zombie.c
	crafting/recipe.h
	crafting/crafting.h
	crafting/crafting.c
	crafting/recipeids.h
	crafting/recipe.c
	screen/crafting_menu.h
	screen/crafting_menu.c
	entity/oven.h
	entity/oven.c
	entity/furnace.c
	entity/furnace.h
	entity/anvil.h
	entity/anvil.c
	entity/chest.h
	entity/chest.c
	screen/container_menu.c
	screen/container_menu.h
	entity/airwizard.c
	entity/airwizard.h
	screen/won_menu.h
	screen/won_menu.c

)
target_include_directories(minicraft-sdl PUBLIC ".")

