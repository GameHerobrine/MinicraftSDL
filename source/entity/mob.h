#ifndef MOB_H
#define MOB_H
#include <entity/entity.h>

struct _Level;

typedef struct _Mob{
	Entity entity;
	int walkDist;
	int dir;
	int hurtTime;
	int xKnockback, yKnockback;
	int maxHealth;
	int health;
	int swimTimer;
	int tickTime;
} Mob;

void mob_create(Mob* mob);
void mob_tick(Mob* mob);
void mob_die(Mob* mob);
uint8_t mob_move(Mob* mob, int xa, int ya);
uint8_t mob_isSwimming(Mob* mob);
uint8_t mob_blocks(Mob* mob, Entity* entity);
void mob_heal(Mob* mob, int heal);
void mob_doHurt(Mob* mob, int damage, int attackDir);
char mob_findStartPos(Mob* mob, struct _Level* level);

#endif // MOB_H
