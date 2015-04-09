#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include "glassSK.h"
#include "r1279.h"
#include "gaussian.h"

GLASS_SK init_sys(){
	// Initialize the Sherrington-Kirkpatrick spin glass system.
	// Return an initialized GLASS_SK structure.

	GLASS_SK sys;
	sys.N = SIZE;	/* number of spins */
	sys.H = H1;		/* external field */

	int i, j;
	/* Initialize sys.sigma, sys.xi */
	for(i = 0; i < sys.N; i++){
		sys.sigma[i] = 1;
		sys.xi[i] = ir1279()%2 * 2 - 1;
	}

	/* Initialize sys.J: allocate memory and asign values */
	sys.J = (double**)malloc(sizeof(double*) * sys.N);
	for(i = 0; i < sys.N; i++)
		sys.J[i] = (double*)malloc(sizeof(double) * sys.N);
	for(i = 0; i < sys.N; i++){
		sys.J[i][i] = 0;
		for(j = 0; j < i; j++)
			sys.J[i][j] = sys.J[j][i] = gauss()/sqrt(sys.N);
	}

	/* Initialize sys.energy */
	sys.energy = 0;
	for(i = 0; i < sys.N; i++){
		sys.energy += - sys.H * sys.xi[i] * sys.sigma[i];
		for(j = 0; j < sys.N; j++)
			sys.energy += - 0.5 * sys.J[i][j] * sys.sigma[i] * sys.sigma[j];
	}

	/* Initialize sys.magnetization */
	sys.magnetization = 0;
	for(i = 0; i < sys.N; i++)
		sys.magnetization += sys.xi[i] * sys.sigma[i];

	/* Initialize sys.h */
	for(i = 0; i < sys.N; i++){
		sys.h[i] = sys.H * sys.xi[i];
		for(j = 0; j < sys.N; j++)
			sys.h[i] += sys.J[i][j] * sys.sigma[j];
	}

	/* Initialize unstable spins */
	identify_unstable(&sys);

	return sys;
}

void identify_unstable(GLASS_SK *sys){
	// Identity unstable spins,
	// then store their indics in sys.flags[],
	// and store the number of unstable spins in sys.unstable_num.
	
	int i;
	sys->unstable_num = 0;
	for(i = 0; i < sys->N; i++){
		if(sys->sigma[i] * sys->h[i] < 0){
			sys->unstable[sys->unstable_num] = i;
			sys->unstable_num += 1;
		}
	}
	for(i = sys->unstable_num; i < sys->N; i++){
		sys->unstable[i] = -1;
	}
}

// void update_spin(GLASS_SK *sys, int s){
// 	// Assume s the index of a flipped spin.
// 	// Update the spin, energy, magnetization, and the local field,
// 	// that is to say, sys.sigma[], sys.energy, sys.magnetization, and sys.h[]
// 	sys->sigma[s] = - sys->sigma[s];
// 	sys->magnetization += 2 * sys->xi[s] * sys->sigma[s];
// 	sys->energy -= 2 * sys->h[s] * sys->sigma[s];
// 	int i;
// 	for(i = 0; i < sys->N; i++)
// 		sys->h[i] += 2 * sys->J[i][s] * sys->sigma[s];
// }

void quench(GLASS_SK *sys){
	// Indentify all the unstable spins, then randomly flip one of them.
	// Update the system after the flipping.
	// Repeat untill all the spins are stable.

	int i, j, s, index;
	double energy, magnetization;

	while(sys->unstable_num > 0){
		s = ir1279()%sys->unstable_num;
		index = sys->unstable[s];
		sys->sigma[index] = - sys->sigma[index];
		sys->energy -= 2 * sys->h[index] * sys->sigma[index];
		sys->magnetization += 2 * sys->xi[index] * sys->sigma[index];
		for(j = 0; j < sys->N; j++)
			sys->h[j] += 2 * sys->J[j][index] * sys->sigma[index];
		identify_unstable(sys);

		/* TEST */
		printf("%f\t%f\n", sys->energy/sys->N, sys->magnetization/sys->N);
		
		energy = 0;
		for(i = 0; i < sys->N; i++){
			energy += - sys->H * sys->xi[i] * sys->sigma[i];
			for(j = 0; j < sys->N; j++)
				energy += - 0.5 * sys->J[i][j] * sys->sigma[i] * sys->sigma[j];
		}
		magnetization = 0;
		for(i = 0; i < sys->N; i++)
			magnetization += sys->xi[i] * sys->sigma[i];
		printf("%f\t%f\n\n", energy/sys->N, magnetization/sys->N);
	}
}

void ac_demag(GLASS_SK *sys){
	while(sys->H >= 0){
		quench(sys);
		sys->H -= 0.001;
	}
}

void print_system_status(GLASS_SK *sys){
	// Print out the current status of the system

	int i, j;
	// printf("Number\tField\n");
	// printf("%d\t%f\n\n", sys->N, sys->H);
	// printf("sigma\txi\th\n");
	// for(i = 0; i <sys->N; i++){
	// 	printf("%d\t%d\t%f\n", sys->sigma[i], sys->xi[i], sys->h[i]);
	// }

	// printf("\nJ[i][j]:\n");
	// for(i = 0; i < sys->N; i++){
	// 	for(j = 0; j < sys->N; j++){
	// 		printf("%f\t", sys->J[i][j]);
	// 	}
	// 	printf("\n");	
	// }

	printf("\nEneryg\t\tMagnetization\n");
	printf("%f\t%f\n\n", sys->energy/sys->N, sys->magnetization/sys->N);

	/* Test teh indentify_unstable*/
	// printf("\nUnstable spins:\n");
	// for(i = 0; i < sys->N; i++){
	// 	printf("%d\n", sys->unstable[i]);
	// }
	printf("Number of unstable spins: %d\n\n", sys->unstable_num);
}
