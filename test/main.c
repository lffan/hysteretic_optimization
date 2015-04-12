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
	double energy = 0, magnetization;

	GLASS_SK sys;
	
	for(i = 0; i < 50; i++){
		sys = init_sys();
		ac_demag(&sys, 1.6);
		energy += sys.energy;
		print_system_status(&sys);
	}
	printf("The average %f\n", energy);


	return 0;
}