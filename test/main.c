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

	printf("# Test... SIZE: %d.\n", SIZE);

	int i, j;
	double energy, magnetization;

	static GLASS_SK sys;
	
	sys = init_sys();
	print_system_status(&sys);
	ac_demag(&sys, 2.0);
	print_system_status(&sys);

	return 0;
}