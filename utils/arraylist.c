#include "arraylist.h"

void create_arraylist(ArrayList* list){
	list->capacity = 0;
	list->size = 0;
	list->elements = 0;
}

void arraylist_push(ArrayList* list, void* element){
	int size = list->size + 1;
	
	if(size > list->capacity){
		if(list->elements){
			list->elements = realloc(list->elements, sizeof(void*) * size);
			printf("realloc\n");
		}else{
			list->elements = malloc(sizeof(void*));
			printf("malloc\n");
		}
		++list->capacity;
	}
	list->size = size;
	
	list->elements[list->size - 1] = element;
}

void* arraylist_get(ArrayList* list, int index){
	return list->elements[index];
}

void* arraylist_pop(ArrayList* list){
	--list->size;
	void* elem = list->elements[list->size];
	return elem;
}

void arraylist_remove_and_dealloc_each(ArrayList* list){
	for(int i = 0; i < list->size; ++i){
		free(list->elements[i]);
	}
	free(list->elements);
}
void arraylist_remove(ArrayList* list){
	free(list->elements);
}
