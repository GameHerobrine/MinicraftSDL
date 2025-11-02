#include "inputhandler.h"
#include <SDL/SDL_keysym.h>
#ifdef NSPIRE
#include <libndls.h>
#include <keys.h>
#endif
Key up = {0, 0, 0, 0};
Key down = {0, 0, 0, 0};
Key left = {0, 0, 0, 0};
Key right = {0, 0, 0, 0};
Key attack = {0, 0, 0, 0};
Key menu = {0, 0, 0, 0};
#ifdef NSPIRE
Key nsp_exit = {0, 0, 0, 0};
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
#ifdef NSPIRE
void input_scan_nspire() {
	if(any_key_pressed()) {
		int kp = 0;
		if(isKeyPressed(KEY_NSPIRE_ESC)) kp |= 64;
		if(isKeyPressed(KEY_NSPIRE_8) || isKeyPressed(KEY_NSPIRE_UP)) kp |= 1;
		if(isKeyPressed(KEY_NSPIRE_2) || isKeyPressed(KEY_NSPIRE_DOWN)) kp |= 2;
		if(isKeyPressed(KEY_NSPIRE_4) || isKeyPressed(KEY_NSPIRE_LEFT)) kp |= 4;
		if(isKeyPressed(KEY_NSPIRE_6) || isKeyPressed(KEY_NSPIRE_RIGHT)) kp |= 8;
		if(!(kp & (1 | 4)) && (isKeyPressed(KEY_NSPIRE_7) || isKeyPressed(KEY_NSPIRE_LEFTUP))) kp |= (1 | 4);
		if(!(kp & (2 | 4)) && (isKeyPressed(KEY_NSPIRE_1) || isKeyPressed(KEY_NSPIRE_DOWNLEFT))) kp |= (2 | 4);
		if(!(kp & (1 | 8)) && (isKeyPressed(KEY_NSPIRE_9) || isKeyPressed(KEY_NSPIRE_UPRIGHT))) kp |= (1 | 8);
		if(!(kp & (2 | 8)) && (isKeyPressed(KEY_NSPIRE_3) || isKeyPressed(KEY_NSPIRE_RIGHTDOWN))) kp |= (2 | 8);

		if(isKeyPressed(KEY_NSPIRE_TAB) || isKeyPressed(KEY_NSPIRE_ENTER) || isKeyPressed(KEY_NSPIRE_RET) || isKeyPressed(KEY_NSPIRE_X)) kp |= 16;
		if(isKeyPressed(KEY_NSPIRE_5) || isKeyPressed(KEY_NSPIRE_CTRL) || isKeyPressed(KEY_NSPIRE_SPACE) || isKeyPressed(KEY_NSPIRE_C)) kp |= 32;

		if(up.down != (kp & 1)) key_toggle(&up, kp & 1);
		if(down.down != (kp & 2)) key_toggle(&down, kp & 2);
		if(left.down != (kp & 4)) key_toggle(&left, kp & 4);
		if(right.down != (kp & 8)) key_toggle(&right, kp & 8);

		if(menu.down != (kp & 16)) key_toggle(&menu, kp & 16);
		if(attack.down != (kp & 32)) key_toggle(&attack, kp & 32);
		if(nsp_exit.down != (kp & 64)) key_toggle(&nsp_exit, kp & 64);
	} else {
		if(up.down != 0) key_toggle(&up, 0);
		if(down.down != 0) key_toggle(&down, 0);
		if(left.down != 0) key_toggle(&left, 0);
		if(right.down != 0) key_toggle(&right, 0);

		if(menu.down != 0) key_toggle(&menu, 0);
		if(attack.down != 0) key_toggle(&attack, 0);
		if(nsp_exit.down != 0) key_toggle(&nsp_exit, 0);
	}
}
#endif
void input_toggle(SDLKey key, char pressed){
	switch(key){
#ifdef NSPIRE
		case SDLK_7:
			key_toggle(&up, pressed);
			key_toggle(&left, pressed);
			break;
		case SDLK_9:
			key_toggle(&up, pressed);
			key_toggle(&right, pressed);
			break;
		case SDLK_1:
			key_toggle(&down, pressed);
			key_toggle(&left, pressed);
			break;
		case SDLK_3:
			key_toggle(&down, pressed);
			key_toggle(&right, pressed);
			break;
#endif

		case SDLK_KP8:
		case SDLK_w:
		case SDLK_UP:
			key_toggle(&up, pressed);
			break;
		case SDLK_KP2:
		case SDLK_s:
		case SDLK_DOWN:
			key_toggle(&down, pressed);
			break;
		case SDLK_KP4:
		case SDLK_a:
		case SDLK_LEFT:
			key_toggle(&left, pressed);
			break;
		case SDLK_KP6:
		case SDLK_d:
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
