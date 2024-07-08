#ifndef PLAYER_H
#define PLAYER_H
#include <entity/inventory.h>
#include "mob.h"
#include <level/level.h>
#include <entity/_player.h>

struct _Item;

typedef struct _Player{
	Mob mob;
	int attackTime, attackDir;
	Inventory inventory;
	struct _Item* attackItem, *activeItem;
	int stamina, staminaRecharge, staminaRechargeDelay;
	int score;
	int maxStamina;
	int onStairDelay;
	int invulnerableTime;
} Player;

void player_create(Player* player);
void player_tick(Player* player);
char player_use(Player* player);
void player_attack(Player* player);
char player_usexy(Player* player, int x0, int y0, int x1, int y1);
char player_interact(Player* player, int x0, int y0, int x1, int y1);
void player_hurt(Player* player, int x0, int y0, int x1, int y1);
int player_getAttackDamage(Player* player, Entity* entity);
void player_render(Player* player, Screen* screen);
//TODO: void player_touchItem(Player* player, _ItemEntity* itemEntity);
char player_findStartPos(Player* player, Level* level);
//TODO findStartPos
//TODO paySTamina
//TODO changeLevel
//TODO getLightRadius
//TODO die
//TODO touchedBy
//TODO doHurt
//TODO gameWon
void player_free(Player* player);

#endif // PLAYER_H
