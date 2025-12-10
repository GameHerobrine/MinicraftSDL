#include <SDL/SDL.h>

#define MAX_SOUNDS 7

int sound_playerHurt = -1, sound_playerDeath = -1, sound_monsterHurt = -1, sound_Test = -1, sound_Pickup = -1, sound_bossDeath = -1, sound_Craft = -1;

static SDL_AudioSpec sound_specs[MAX_SOUNDS];
static uint32_t sound_wavlengths[MAX_SOUNDS];
static uint8_t* sound_wavbuffers[MAX_SOUNDS];

static int lastSoundId = 0;
static int load_sound(const char* path) {
	if(lastSoundId >= MAX_SOUNDS) {
		printf("Attempted to load a sound but reached max amount of sounds!\n");
		return -1;
	}
	if(!SDL_LoadWAV(path, sound_specs + lastSoundId, sound_wavbuffers + lastSoundId, sound_wavlengths + lastSoundId)) {
		printf("Failed to load a sound %s: %s\n", path, SDL_GetError());
		return -1;
	}

	return lastSoundId++;
}
static SDL_AudioSpec wanted;
static Uint8* audio_chunk;
static Uint32 audio_len;
static Uint8* audio_pos;
static void fill_audio(void* udata, Uint8* stream, int len) {
	if(audio_len == 0) {
		SDL_PauseAudio(1);
		return;
	}

	len = (len > audio_len ? audio_len : len);
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
	audio_pos += len;
	audio_len -= len;
}
void _play_sound(int id) {
	audio_chunk = sound_wavbuffers[id];
	audio_len = sound_wavlengths[id];
	audio_pos = audio_chunk;
	SDL_PauseAudio(0);
}

void init_sounds() {
	printf("Initializing sounds...\n");

	wanted.freq = 22050;
	wanted.format = AUDIO_S16;
	wanted.channels = 2;
	wanted.samples = 1024;
	wanted.callback = fill_audio;
	wanted.userdata = NULL;
	if(SDL_OpenAudio(&wanted, NULL) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		return;
	}

	sound_Test = load_sound("sounds/test.wav");
	sound_playerHurt = load_sound("sounds/playerhurt.wav");
	sound_Pickup = load_sound("sounds/pickup.wav");
	sound_monsterHurt = load_sound("sounds/monsterhurt.wav");
	sound_playerDeath = load_sound("sounds/death.wav");
	sound_Craft = load_sound("sounds/craft.wav");
	sound_bossDeath = load_sound("sounds/bossdeath.wav");
}



void free_sounds() {
	for(int i = 0; i < lastSoundId; ++i) {
		SDL_FreeWAV(sound_wavbuffers[i]);
	}
	SDL_CloseAudio();
}
