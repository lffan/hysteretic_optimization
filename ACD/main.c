#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "r1279.h"
#include "gaussian.h"
#include "glassSK.h"

long seedgen(void);

int main(){

	long seed;
	seed = seedgen();
	setr1279(seed);

	printf("# Test... SIZE: %d.\n\n", SIZE);

	int i, j, times;
	double energy = 0, magnetization;

	GLASS_SK sys;
	sys = init_sys();

	times = ac_demag(&sys, 2.0);
	printf("Stable energy: %f\n", sys.energy_stable/sys.N);
	printf("Cycle times: %d\n", times);


	return 0;
}