#ifndef ITEM_RESOURCE_FOOD_RESOURCE_H_
#define ITEM_RESOURCE_FOOD_RESOURCE_H_

struct _resource;

typedef struct{
	int heal;
	int staminaCost;
} res_food;

void init_food_resource(struct _resource* resource, char* name, int sprite, int color, int heal, int staminaCost);

#endif /* ITEM_RESOURCE_FOOD_RESOURCE_H_ */
