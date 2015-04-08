#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include "glassSK.h"
#include "r1279.h"
#include "gaussian.h"

GLASS_SK init_sys(){
	// Initialize the Sherrington-Kirkpatrick spin glass system
	// Return an initialized GLASS_SK structure

	GLASS_SK sys;
	sys.N = SIZE;
	sys.H = H1;		/* external field */

	int i, j;
	/* Initialize sys.sigma, sys.J, sys.xi*/
	for(i = 0; i < sys.N; i++){
		sys.sigma[i] = 1;
		sys.xi[i] = ir1279()%2 * 2 - 1;
		sys.J[i][i] = 0;
		for(j = 0; j < i; j++)
			sys.J[i][j] = sys.J[j][i] = gauss()/sqrt(sys.N);
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

	/* Initialize unstable spins */
	for(i = 0; i < sys.N; i++){
		sys.unstable[i] = -1;
	}
	sys.unstable_num = 0;

	return sys;
}

void identify_unstable(GLASS_SK *sys){
	// Identity unstable spins,
	// then store their indics in sys.flags[],
	// and store the number of unstable spins in sys.unstable_num
	
	int i;
	sys->unstable_num = 0;
	for(i = 0; i < sys->N; i++){
		if(sys->sigma[i] * sys->h[i] < 0){
			sys->unstable[sys->unstable_num] = i;
			sys->unstable_num += 1;
		}
	}
}

void print_system_status(GLASS_SK *sys){
	// Print out the current status of the system

	int i, j;
	printf("Number\tField\n");
	printf("%d\t%f\n\n", sys->N, sys->H);
	printf("sigma\txi\th\n");
	for(i = 0; i <sys->N; i++){
		printf("%d\t%d\t%f\n", sys->sigma[i], sys->xi[i], sys->h[i]);
	}
	// printf("\nJ[i][j]:\n");
	// for(i = 0; i < sys->N; i++){
	// 	for(j = 0; j < sys->N; j++){
	// 		printf("%f\t", sys->J[i][j]);
	// 	}
	// 	printf("\n");	
	// }
	printf("\nEneryg\t\tMagnetization\n");
	printf("%f\t%f\n", sys->energy, sys->magnetization);

	/* Test teh indentify_unstable*/
	identify_unstable(sys);
	printf("\nUnstable spins:\n");
	for(i = 0; i < sys->N; i++){
		printf("%d\n", sys->unstable[i]);
	}
	printf("Number of unstable spins: %d\n", sys->unstable_num);
}

void update_en_mag(GLASS_SK *sys, int s){
	// Assume s the index of a flipped spin
	// Update the spin, energy, magnetization, and the local field,
	// that is to say, sys.sigma[], sys.energy, sys.magnetization, and sys.h[]
	int i;
	sys->sigma[s] = - sys->sigma[s];
	sys->magnetization += 2 * sys->xi[s] * sys->sigma[s];
	for(i = 0; i < sys->N; i++){
		sys->h[i] += 2 * sys->sigma[i] * sys->sigma[s];
	}
}


