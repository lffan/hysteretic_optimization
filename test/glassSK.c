#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include "glassSK.h"
#include "r1279.h"
#include "gaussian.h"

GLASS_SK init_sys(){
	/* Initialize the SK system */

	GLASS_SK sys;
	sys.N = SIZE;
	sys.H = H1;

	int i, j;
	/* Initialize sys.sigma, sys.J, sys.xi*/
	for(i = 0; i < sys.N; i++){
		sys.sigma[i] = 1;
		sys.J[i][i] = 0;
		sys.xi[i] = ir1279()%2 * 2 - 1;
		for(j = 0; j < i; j++)
			sys.J[i][j] = sys.J[j][i] = gauss();
	}

	/* Initialize sys.h, sys.energy, sys.magnetization*/
	sys.energy = 0;
	sys.magnetization = 0;
	for(i = 0; i < sys.N; i++){
		sys.h[i] = sys.H * sys.xi[i];
		sys.energy += - sys.H * sys.xi[i] * sys.sigma[i];
		sys.magnetization += sys.xi[i] * sys.sigma[i];
		for(j = 0; j < sys.N; j++){
			sys.h[i] += sys.J[i][j] * sys.sigma[j];
			sys.energy += - 0.5 * sys.J[i][j] * sys.sigma[i] * sys.sigma[j];
		}
	}

	return sys;
}

void update_h(GLASS_SK * sys, int s){
	int i, j;
}
