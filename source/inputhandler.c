#include "inputhandler.h"
#include <SDL/SDL_keysym.h>

Key up;
Key down;
Key left;
Key right;
Key attack;
Key menu;
#ifdef NSPIRE
Key nsp_exit;
#endif
void key_toggle(Key* key, char pressed){
	if(pressed != key->down){
		key->down = pressed;
	}
	
	if(pressed) ++key->presses;
}
void key_tick(Key* key){
	if(key->absorbs < key->presses){
		++key->absorbs;
		key->clicked = 1;
	}else{
		key->clicked = 0;
	}
}

void input_tick(){
	key_tick(&up);
	key_tick(&down);
	key_tick(&left);
	key_tick(&right);
	key_tick(&attack);
	key_tick(&menu);
#ifdef NSPIRE
	key_tick(&nsp_exit);
#endif
}

void input_toggle(SDLKey key, char pressed){
	switch(key){
		case SDLK_KP8:
#ifdef NSPIRE
		case SDLK_8:
#else
		case SDLK_w:
#endif
		case SDLK_UP:
			key_toggle(&up, pressed);
			break;
		case SDLK_KP2:
#ifdef NSPIRE
		case SDLK_2:
#else
		case SDLK_s:
#endif
		case SDLK_DOWN:
			key_toggle(&down, pressed);
			break;
		case SDLK_KP4:
#ifdef NSPIRE
		case SDLK_4:
#else
		case SDLK_a:
#endif
		case SDLK_LEFT:
			key_toggle(&left, pressed);
			break;
		case SDLK_KP6:
#ifdef NSPIRE
		case SDLK_6:
#else
		case SDLK_6:
#endif
		case SDLK_RIGHT:
			key_toggle(&right, pressed);
			break;
		case SDLK_TAB:
		case SDLK_LALT:
		case SDLK_RALT:
		case SDLK_RETURN:
		case SDLK_x:
			key_toggle(&menu, pressed);
			break;
		case SDLK_SPACE:
		case SDLK_LCTRL:
		case SDLK_KP0:
		case SDLK_INSERT:
		case SDLK_c:
#ifdef NSPIRE
		case SDLK_5:
#endif
			key_toggle(&attack, pressed);
			break;
		default:
			break;
#ifdef NSPIRE
		case SDLK_ESCAPE:
			key_toggle(&nsp_exit, pressed);
			break;
#endif
	}
}
