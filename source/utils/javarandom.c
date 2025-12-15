#include "javarandom.h"
#include <math.h>

extern inline int random_next_int(Random* random, int bound){
	
	int r = random_next(random, 31);
	int m = bound - 1;
	if(bound & m){
		for(int u = r; u - (r = u % bound) + m < 0; u = random_next(random, 31));
	}else{
		r = ((bound * (long long int)r) >> 31);
	}

	return r;
}
extern inline float random_next_float(Random* random){
	return random_next(random, 24) / (float)(1 << 24);
}

extern inline double random_next_double(Random* random){
	return (((long long int)(random_next(random, 26)) << 27) + random_next(random, 27)) * (1.0 / ((long long int)1 << 53));
}

float random_next_gaussian(Random* random){
	if(random->haveNextNextGaussian){
		random->haveNextNextGaussian = 0;
		return random->nextNextGaussian;
	}

	float v1, v2, s;
	do{
		v1 = 2 * random_next_double(random) - 1;
		v2 = 2 * random_next_double(random) - 1;
		s = v1*v1 + v2*v2;
	}while(s >= 1 || s == 0);
	float multiplier = sqrt(-2 * log(s)/s);
	random->nextNextGaussian = v2 * multiplier;
	random->haveNextNextGaussian = 1;
	return v1*multiplier;
}
