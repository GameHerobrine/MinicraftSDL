#ifndef LEVEL_LEVELGEN_LEVELGEN_H_
#define LEVEL_LEVELGEN_LEVELGEN_H_

typedef struct{
	double* values;
	int w;
	int h;
} LevelGen;

void levelgen_preinit();
void createAndValidateTopMap(unsigned char** map_r, unsigned char** data_r, int w, int h);
void createAndValidateUndergroundMap(unsigned char** map_r, unsigned char** data_r, int w, int h, int depth);

#endif /* LEVEL_LEVELGEN_LEVELGEN_H_ */
