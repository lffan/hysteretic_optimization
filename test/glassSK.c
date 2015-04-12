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

int quench(GLASS_SK *sys){
	// Indentify all the unstable spins, then randomly flip one of them.
	// Update the system after the flipping.
	// Repeat untill all the spins are stable.

	int s, flag = 0;
	identify_unstable(sys);
	while(sys->unstable_num > 0){
		s = ir1279()%sys->unstable_num;
		flip_spin(sys, sys->unstable[s]);
		identify_unstable(sys);
		flag = 1;
	}
	/* If a quench is applied, return 1, otherwise return 0 */
	return flag;
}

int half_cycle(GLASS_SK *sys, double H1, double H2){
	// Quench the system from H1 to H2 with a step of h
	// When go across 0, record the minimum energy and the best configuration
	printf("########## half_cycle ############\n\n");

	int i, j, quench_time = 0;
	double h;

	/* Quench form H1 to 0 */
	sys->H = H1;
	update_sys(sys);
	h = H1 / 20.0;
	for(i = 0; i < 19; i++){
		quench_time += quench(sys);
		sys->H -= h;
		update_sys(sys);
	}
	print_system_status(sys);
	/* Quench at 0 */
	sys->H = 0;
	update_sys(sys);
	quench_time += quench(sys);
	/* Check the best configuration */
	if(sys->energy_stable > sys->energy){
		sys->energy_stable = sys->energy;
		for(i = 0; i < sys->N; i++)
			sys->sigma_best[i] = sys->sigma[i];
	}
	print_system_status(sys);
	/* Quench from 0 to H2 */
	h = - H2 / 20.0;
	sys->H -= h;
	for(i = 0; i < 19; i++){
		quench_time += quench(sys);
		sys->H -= h;
		update_sys(sys);
	}
	print_system_status(sys);

	return quench_time;
}

double rand_gamma(){
	// Return a random number in [0.8, 1.0]
	double g;
	g = 0.8 + 0.2 * r1279();
	return g;
}

int ac_demag(GLASS_SK *sys, double H0){
	// AC demagnetization starting from H0

	int i, j, quench_time, cycle_time;
	double h1, h2;
	h1 = H0;
	h2 = - rand_gamma() * h1;
	quench_time = half_cycle(sys, h1, h2);
	if(quench_time > 0){
		cycle_time += 1;
	}
	/* Repeat cycles until there is no quench happening in one cycle */
	while(quench_time > 0){
		h1 = h2;
		h2 = - rand_gamma() * h1;
		quench_time = half_cycle(sys, h1, h2);
		cycle_time += 1;
	}

	return cycle_time;
}

void shake(GLASS_SK *sys){
	// Shake the system
}

void print_system_status(GLASS_SK *sys){
	// Print out the current status of the system

	int i, j;
	printf("Number\tField\n");
	printf("%d\t\t%f\n", sys->N, sys->H);
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
	printf("%f\t%f\n\n", sys->energy/sys->N, sys->magnetization/sys->N);
	// printf("\nThe minimum energy:%f\n\n", sys->energy_stable);

	/* Test teh indentify_unstable*/
	// printf("\nUnstable spins:\n");
	// for(i = 0; i < sys->N; i++){
	// 	printf("%d\n", sys->unstable[i]);
	// }

	// printf("Number of unstable spins: %d\n\n", sys->unstable_num);
}
