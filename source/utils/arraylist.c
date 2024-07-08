#include "arraylist.h"
#include <string.h>
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
void* arraylist_removeElement(ArrayList* list, void* element){
	for(int i = 0; i < list->size; ++i){
		void* e = list->elements[i];
		if(e == element){
			return arraylist_removeId(list, i);
		}
	}

	printf("Tried removing unknown element from array (%p)!\n", element);
}
void* arraylist_removeId(ArrayList* list, int index){
	void* element = list->elements[index];
	if(index < list->size-1){
		memcpy(list->elements + index, list->elements + index + 1, sizeof(*list->elements)*(list->size - index));
	}
	--list->size;
	return element;
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

void arraylist_clear(ArrayList* list){
	list->size = 0;
}
