#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gaussian.h"

long seedgen(void);

int main(){

	long seed;
	seed = seedgen();
	setr1279(seed);

	int i;
	double x, sumx, sumx2;
	for(i = 0; i < 100000; i++){
		x = gauss();
		sumx += x;
		sumx2 += x*x;
	}
	printf("%f\t%f\n", sumx/100000, sumx2/100000);

	return 0;
}