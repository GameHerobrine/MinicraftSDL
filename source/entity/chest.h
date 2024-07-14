#ifndef CHEST_H
#define CHEST_H
#include <entity/furniture.h>
#include <entity/inventory.h>

typedef struct _Chest{
	Furniture furniture;
	Inventory inventory;
} Chest;

void chest_create(Chest* chest);
char chest_use(Chest* chest, struct _Player* player, int attackDir);
void chest_free(Chest* chest);

#endif // CHEST_H
