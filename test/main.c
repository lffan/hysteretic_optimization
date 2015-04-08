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

	static GLASS_SK sys;
	sys = init_sys();

	print_system_status(&sys);
	printf("\n## Quench once:\n\n");
	quench(&sys);
	print_system_status(&sys);

	int i, j;
	sys.energy = 0;
	sys.magnetization = 0;
	for(i = 0; i < sys.N; i++){
		sys.h[i] = sys.H * sys.xi[i];
		sys.magnetization += sys.xi[i] * sys.sigma[i];
		for(j = 0; j < sys.N; j++){
			sys.h[i] += sys.J[i][j] * sys.sigma[j];
			sys.energy += - 0.5 * sys.J[i][j] * sys.sigma[i] * sys.sigma[j];
		}
	}
	printf("%f\t%f\n", sys.energy/sys.N, sys.magnetization/sys.N);


	return 0;
}