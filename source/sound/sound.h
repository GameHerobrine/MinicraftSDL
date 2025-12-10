#ifndef _SOUNDS_H
#define _SOUNDS_H
#ifdef SOUNDS
void _play_sound(int id);
#define sound_play(id) _play_sound(id)
#else
#define sound_play(id)
#endif
extern int sound_playerHurt, sound_playerDeath, sound_monsterHurt, sound_Test, sound_Pickup, sound_bossDeath, sound_Craft;
void init_sounds();
void free_sounds();

#endif
