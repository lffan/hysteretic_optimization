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

	GLASS_SK sys;
	sys = init_sys();


	/* Test the function init_sys()*/
	int i, j;
	printf("%d\t%f\n", sys.N, sys.H);
	for(i = 0; i <sys.N; i++){
		printf("%d\t%d\t%f\n", sys.sigma[i], sys.xi[i], sys.h[i]);
	}
	for(i = 0; i < sys.N; i++){
		for(j = 0; j < sys.N; j++){
			printf("%f\t", sys.J[i][j]);
		}
		printf("\n");	
	}
	printf("%f\t%f\n", sys.energy, sys.magnetization);

	return 0;
}