#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <SDL/SDL_keysym.h>

typedef struct{
	int presses, absorbs;
	char down, clicked;
} Key;

extern Key up, down, left, right, attack, menu;

void key_toggle(Key* key, char pressed);
void key_tick(Key* key);

void input_toggle(SDLKey key, char pressed);
void input_tick();

#endif /* INPUTHANDLER_H_ */
