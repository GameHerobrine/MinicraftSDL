#ifndef UTILS_JAVARANDOM_H_
#define UTILS_JAVARANDOM_H_

typedef struct{
	long long int seed;
	float nextNextGaussian;
} Random;

void random_set_seed(Random* random, int seed);
int random_next(Random* random, int bits);
int random_next_int(Random* random, int bound);
float random_next_float(Random* random);

#endif /* UTILS_JAVARANDOM_H_ */
