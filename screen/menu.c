#include "menu.h"
#include "../utils/arraylist.h"
#include "list_item.h"
#include "../gfx/font.h"
#include "../gfx/screen.h"
#include "../gfx/color.h"

#include "title_menu.h"
#include "about_menu.h"
#define MENUS_SIZE 16
char _next[] = ">";
char _prev[] = "<";
menu_vt* menus[MENUS_SIZE];

enum menu_id menu_parent;

void init_menus(){
	
	for(int i = 0; i < MENUS_SIZE; ++i){
		menus[i] = 0;
	}
	
	menus[mid_TITLE] = &titlemenu_vt;
	menus[mid_ABOUT] = &aboutmenu_vt;
}

void tick_menu(enum menu_id menu){
	if(menus[menu]){
		menus[menu]->tick();
	}else{
		printf("Tried ticking non existent menu(%d)\n", menu);
	}
}
void render_menu(enum menu_id menu, Screen* screen){
	if(menus[menu]){
		menus[menu]->render(screen);
	}else{
		printf("Tried rendering non existent menu(%d)\n", menu);
	}
}
void init_menu(enum menu_id menu){
	if(menus[menu]){
		menus[menu]->init();
	}else{
		printf("Tried init non existent menu(%d)\n", menu);
	}
}

void menu_render_item_list(Screen* screen, int xo, int yo, int x1, int y1, ArrayList* listItems, int selected){
	char renderCursor = 1;
	if(selected < 0){
		selected = -selected - 1;
		renderCursor = 0;
	}
	
	int w = x1 - xo;
	int h = y1 - yo - 1;
	int i0 = 0;
	int i1 = listItems->size;
	if(i1 > h) i1 = h;
	int io = selected - h / 2;
	if(io > listItems->size - h){
		io = listItems->size - h;
	}
	if(io < 0) io = 0;
	
	for(int i = i0; i < i1; ++i){
		list_item_vt* item = arraylist_get(listItems, i + io);
		item->renderInventory(screen, (1 + xo)*8, (i + 1 + yo)*8);
	}
	
	if(renderCursor){
		int yy = selected + 1 - io + yo;
		font_draw(_next, strlen(_next), screen, (xo + 0)*8, yy*8, getColor4(5, 555, 555, 555));
		font_draw(_prev, strlen(_prev), screen, (xo + 0)*8, yy*8, getColor4(5, 555, 555, 555));
	}
}
