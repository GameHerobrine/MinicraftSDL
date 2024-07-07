#include "javarandom.h"
static const long long int multiplier = 0x5DEECE66D;
static const long long int mask = ((long long int)1 << 48) - 1;
static const long long int addend = 0xB;

void random_set_seed(Random* random, int seed){
	random->seed = (seed ^ multiplier) & mask;
}

int random_next(Random* random, int bits){
	long long int oldseed = 0, nextseed = 0;
	long long int seed = random->seed;
	
	oldseed = seed;
	nextseed = (oldseed * multiplier + addend) & mask;
	
	random->seed = nextseed;
	
	return (int)((unsigned long long int)nextseed >> (48 - bits));
}
char random_next_boolean(Random* random){
	return random_next(random, 1) != 0;
}
int random_next_int(Random* random, int bound){
	
	int r = random_next(random, 31);
	int m = bound - 1;
	if(bound & m){
		for(int u = r; u - (r = u % bound) + m < 0; u = random_next(random, 31));
	}else{
		r = ((bound * (long long int)r) >> 31);
	}

	return r;
}
float random_next_float(Random* random){
	return random_next(random, 24) / (float)(1 << 24);
}
