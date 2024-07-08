#include "tile.h"
#include "grass_tile.h"
#include "water_tile.h"
#include "flower_tile.h"
#include "tree_tile.h"

#include "sand_tile.h"
#include "cactus_tile.h"
#include "hole_tile.h"
#include "sapling_tile.h"


#include "lava_tile.h"
#include "stairs_tile.h"


#include "hard_rock_tile.h"
#include "ore_tile.h"
#include "cloud_cactus_tile.h"
#include <gfx/screen.h>
#include <item/resource/resource.h>
#include "../level.h"

#include <entity/entity.h>
#include <entity/mob.h>
#include <entity/_entity_caller.h>

Tile tiles[256];
int tile_tickCount = 0;

void init_tiles(){
	
	for(int i = 0; i < 256; ++i){
		memset(tiles + i, 0, sizeof(Tile));
	}
	
	grasstile_init(GRASS);
	tile_init(ROCK);
	watertile_init(WATER);
	flowertile_init(FLOWER);
	treetile_init(TREE);
	tile_init(DIRT);
	sandtile_init(SAND);
	cactustile_init(CACTUS);
	holetile_init(HOLE);
	saplingtile_init(TREE_SAPLING, GRASS, TREE);
	saplingtile_init(CACTUS_SAPLING, SAND, CACTUS);
	tile_init(FARMLAND);
	wheat_tile_init(WHEAT);
	lavatile_init(LAVA);
	stairstile_init(STAIRS_DOWN, 0);
	stairstile_init(STAIRS_UP, 1);
	tile_init(INFINITE_FALL);
	tile_init(CLOUD);
	tile_init(HARD_ROCK);
	oretile_init(IRON_ORE, &ironOre);
	oretile_init(GOLD_ORE, &goldOre);
	oretile_init(GEM_ORE, &gem);
	tile_init(CLOUD_CACTUS);
}

void tile_init(TileID id){
	Tile* t = tiles + id;
	t->connectsToGrass = t->connectsToLava = t->connectsToSand = t->connectsToWater = 0;
	t->id = id;
}

void tile_render(TileID id, Screen* screen, Level* level, int x, int y){
	switch(id){
		case CACTUS:
			cactustile_render(id, screen, level, x, y);
			break;
		case CLOUD_CACTUS:
			cloudcactustile_render(id, screen, level, x, y);
			break;
		case CLOUD:
			cloudtile_render(id, screen, level, x, y);
			break;
		case DIRT:
			dirttile_render(id, screen, level, x, y);
			break;
		case FARMLAND:
			farmlandtile_render(id, screen, level, x, y);
			break;
		case FLOWER:
			flowertile_render(id, screen, level, x, y);
			break;
		case GRASS:
			grasstile_render(id, screen, level, x, y);
			break;
		case HARD_ROCK:
			hardrocktile_render(id, screen, level, x, y);
			break;
		case HOLE:
			holetile_render(id, screen, level, x, y);
			break;
		case LAVA:
			lavatile_render(id, screen, level, x, y);
			break;
		case IRON_ORE:
		case GOLD_ORE:
		case GEM_ORE:
			oretile_render(id, screen, level, x, y);
			break;
		case ROCK:
			rocktile_render(id, screen, level, x, y);
			break;
		case SAND:
			sandtile_render(id, screen, level, x, y);
			break;
		case TREE_SAPLING:
		case CACTUS_SAPLING:
			saplingtile_render(id, screen, level, x, y);
			break;
		case STAIRS_UP:
		case STAIRS_DOWN:
			stairstile_render(id, screen, level, x, y);
			break;
		//case STONE: XXX unused?
		//	
		//	break;
		case TREE:
			treetile_render(id, screen, level, x, y);
			break;
		case WATER:
			watertile_render(id, screen, level, x, y);
			break;
		case WHEAT:
			wheattile_render(id, screen, level, x, y);
			break;
		default:
		case INFINITE_FALL:
			//render nothing
			break;
	}
}

char tile_mayPass(TileID id, Level* level, int x, int y, Entity* e){
	switch(id){ //TODO WIP
		case CACTUS:
		case HARD_ROCK:
		case GEM_ORE:
		case GOLD_ORE:
		case IRON_ORE:
		case ROCK:
		//XXX unused case STONE:
		case TREE:
			return 0;
		case CLOUD_CACTUS:
		case INFINITE_FALL:
			if(e->type == AIRWIZARD) return 1;
			return 0;
		case HOLE:
		case LAVA:
		case WATER:
			return call_entity_canSwim(e);
		case CLOUD:
		default:
			return 1;
	}
}

int tile_getLightRadius(TileID id, Level* level, int x, int y){
	switch(id){
		case LAVA:
			return 6;
		default:
			return 0;
	}
}

void tile_hurt(TileID id, Level* level, int x, int y, Mob* source, int dmg, int attackDir){
	switch(id){
		case CACTUS:
			cactus_hurt(id, level, x, y, source, dmg, attackDir);
			break;
		case CLOUD_CACTUS:
			cloudcactus_hurt(id, level, x, y, source, dmg, attackDir);
			break;
		case FLOWER:
			flowertile_hurt(id, level, x, y, source, dmg, attackDir);
			break;
		case HARD_ROCK:
			//TODO
			break;
		case GEM_ORE:
		case GOLD_ORE:
		case IRON_ORE:
			//TODO
			break;
		case ROCK:
			rocktile_hurt(id, level, x, y, source, dmg, attackDir);
			break;
		case CACTUS_SAPLING:
		case TREE_SAPLING:
			//TODO
			break;
		case TREE:
			treetile_hurt(id, level, x, y, source, dmg, attackDir);
			break;
		case WHEAT:
			//TODO
			break;
		default:
			break;
	}

	//TODO
}

//void tile_bumpedInto(TileID id, Level* level, int x, int y, Entity* entity){} //TODO Level*, Entity*

void tile_tick(TileID id, Level* level, int xt, int yt){
	switch(id){
		case CACTUS:
			cactustile_tick(id, level, xt, yt);
			break;
		case FARMLAND:
			farmland_tick(id, level, xt, yt);
			break;
		case GRASS:
			grasstile_tick(id, level, xt, yt);
			break;
		case HARD_ROCK:
			hardrocktile_tick(id, level, xt, yt);
			break;
		case LAVA:
			lavatile_tick(id, level, xt, yt);
			break;
		case ROCK:
			rocktile_tick(id, level, xt, yt);
			break;
		case SAND:
			sandtile_tick(id, level, xt, yt);
			break;
		case TREE_SAPLING:
		case CACTUS_SAPLING:
			saplingtile_tick(id, level, xt, yt);
			break;
		case TREE:
			treetile_tick(id, level, xt, yt);
			break;
		case WATER:
			watertile_tick(id, level, xt, yt);
			break;
		case WHEAT:
			wheattile_tick(id, level, xt, yt);
			break;
		case INFINITE_FALL:
		default:
			//do nothing
			break;
	}
}

//void tile_steppedOns(TileID id, Level* level, int x, int y, Entity* entity){} //TODO Level*, Entity*

//void tile_interact(TileID id, Level* level, int xt, int yt, Player* player, Item* item, int attackDir){} TODO Level*, Player*, Item*

//void tile_use(TileID id, Level* level, int xt, int yt, Player* player, int attackDir){} TODO Level*, Player*

char tile_connectsToLiquid(TileID id){
	return tiles[id].connectsToWater || tiles[id].connectsToLava;
}
