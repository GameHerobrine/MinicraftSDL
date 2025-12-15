#ifndef UTILS_JAVARANDOM_H_
#define UTILS_JAVARANDOM_H_

typedef struct{
	long long int seed;
	float nextNextGaussian;
	char haveNextNextGaussian;
} Random;

static const long long int multiplier = 0x5DEECE66D;
static const long long int mask = ((long long int)1 << 48) - 1;
static const long long int addend = 0xB;
static inline void random_set_seed(Random* random, int seed){
	random->seed = (seed ^ multiplier) & mask;
	random->haveNextNextGaussian = 0;
}
static inline int random_next(Random* random, int bits){
	long long int oldseed = 0, nextseed = 0;
	long long int seed = random->seed;

	oldseed = seed;
	nextseed = (oldseed * multiplier + addend) & mask;

	random->seed = nextseed;

	return (int)((unsigned long long int)nextseed >> (48 - bits));
}

static inline char random_next_boolean(Random* random){
	return random_next(random, 1) != 0;
}
int random_next_int(Random* random, int bound);
float random_next_float(Random* random);
float random_next_gaussian(Random* random);

#endif /* UTILS_JAVARANDOM_H_ */
