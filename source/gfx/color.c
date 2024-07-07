#include "color.h"

int getColor(int d){
	if(d < 0) return 255;

	int r = d / 100 % 10;
	int g = d / 10 % 10;
	int b = d % 10;

	return r * 36 + g * 6 + b;
}

int getColor4(int a, int b, int c, int d){
	return (getColor(d) << 24) + (getColor(c) << 16) + (getColor(b) << 8) + getColor(a);
}
