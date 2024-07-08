#ifndef TOOLTYPE_H
#define TOOLTYPE_H

typedef enum{
	SHOVEL = 0,
	HOE = 1,
	SWORD = 2,
	PICKAXE = 3,
	AXE = 4
} ToolType;

char* getName(ToolType type);

#endif // TOOLTYPE_H
