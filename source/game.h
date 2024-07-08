#include "gfx/spritesheet.h"
#include <entity/player.h>
#include <screen/menu.h>

extern SpriteSheet icons_spritesheet;
extern Player* game_player;

void game_reset();
void game_set_menu(enum menu_id menu);

#define HEIGHT 120
#define WIDTH 160
#define SCALE 3
