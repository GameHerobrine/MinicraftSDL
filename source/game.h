#include "gfx/spritesheet.h"
#include <entity/player.h>
#include <screen/menu.h>

extern Player* game_player;
extern int game_gameTime;
extern int game_pendingLevelChange;
extern char isingame;
#ifdef NSPIRE
extern uint16_t* _nsp_screenbuf;
#endif
void game_reset();
void game_set_menu(enum menu_id menu);
void game_won();

#define HEIGHT 120
#define WIDTH 160

#ifndef NSPIRE
#define SCALE 3
#else
#define SCALE 2
#endif
