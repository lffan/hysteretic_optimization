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

	/* Initialize sys.N */
	sys.N = SIZE;

	int i, j;
	/* Initialize sys.sigma, sys.xi */
	for(i = 0; i < sys.N; i++){
		sys.sigma[i] = sys.xi[i] = ir1279()%2 * 2 - 1;
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

	return sys;
}

void update_sys(GLASS_SK *sys){
	// Given sys.N, sys.H, sys.sigma[], sys.J[][], and sys.xi[],
	// calculate the magnetization, the energy, and the local field.
	
	int i, j;
	/* sys.magnetization */
	sys->magnetization = 0;
	for(i = 0; i < sys->N; i++)
		sys->magnetization += sys->xi[i] * sys->sigma[i];

	/* sys.energy */
	sys->energy = - sys->H * sys->magnetization;
	for(i = 0; i < sys->N; i++)
		for(j = 0; j < sys->N; j++)
			sys->energy += - 0.5 * sys->J[i][j] * sys->sigma[i] * sys->sigma[j];

	/* local field: sys.h */
	for(i = 0; i < sys->N; i++){
		sys->h[i] = sys->H * sys->xi[i];
		for(j = 0; j < sys->N; j++)
			sys->h[i] += sys->J[i][j] * sys->sigma[j];
	}
}

void identify_unstable(GLASS_SK *sys){
	// Identity unstable spins, then store their indics in sys.unstable[],
	// and store the total number of unstable spins in sys.unstable_num.
	
	int i;
	sys->unstable_num = 0;
	for(i = 0; i < sys->N; i++){
		/* If the spin opposites the local field, record the index of it */
		if(sys->sigma[i] * sys->h[i] < 0){
			sys->unstable[sys->unstable_num] = i;
			sys->unstable_num += 1;
		}
	}
	for(i = sys->unstable_num; i < sys->N; i++){
		sys->unstable[i] = -1;
	}
}

void flip_spin(GLASS_SK *sys, int s){
	// Assume s the index of a flipped spin.
	// Update the spin, energy, magnetization, and the local field,
	// that is to say, sys.sigma[], sys.energy, sys.magnetization, and sys.h[]

	sys->sigma[s] = - sys->sigma[s];
	sys->magnetization += 2 * sys->xi[s] * sys->sigma[s];
	sys->energy -= 2 * sys->h[s] * sys->sigma[s];
	int i;
	for(i = 0; i < sys->N; i++)
		sys->h[i] += 2 * sys->J[i][s] * sys->sigma[s];
}

void quench(GLASS_SK *sys){
	// Indentify all the unstable spins, then randomly flip one of them.
	// Update the system after the flipping.
	// Repeat untill all the spins are stable.

	int i, j, s;
	identify_unstable(sys);
	while(sys->unstable_num > 0){
		s = ir1279()%sys->unstable_num;
		flip_spin(sys, sys->unstable[s]);
		identify_unstable(sys);
	}
}

void half_cycle(GLASS_SK *sys, double H1, double H2){
	// Quench the system from H1 to H2 with a step of h
	// When go across 0, record the minimum energy and the best configuration

	int i, j;
	double delta_h = 0.01;
	sys->H = H1;
}

void ac_demag(GLASS_SK *sys, double H0){
	// AC demagnetization
	double h1, h2;
	h1 = H0;
	h2 = - 0.9 * h1;
	while(fabs(h2) > 0.01){
		half_cycle(sys, h1, h2);
		h1 = h2;
		h2 = - 0.9 * h2;
	}
	// sys->H = 0;
	// quench(sys);
}

void print_system_status(GLASS_SK *sys){
	// Print out the current status of the system

	int i, j;
	printf("Number\tField\n");
	printf("%d\t\t%f\n\n", sys->N, sys->H);
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

	// for(i = 0; i < sys->N; i++)
	// 	printf("%4d\t%f\n", sys->sigma[i], sys->h[i]);

	printf("\nEneryg\t\tMagnetization\n");
	printf("%f\t%f\n\n", sys->energy, sys->magnetization);
	// printf("\nThe minimum energy:%f\n\n", sys->energy_stable);

	/* Test teh indentify_unstable*/
	// printf("\nUnstable spins:\n");
	// for(i = 0; i < sys->N; i++){
	// 	printf("%d\n", sys->unstable[i]);
	// }

	// printf("Number of unstable spins: %d\n\n", sys->unstable_num);
}
