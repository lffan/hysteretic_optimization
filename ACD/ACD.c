/****************************************************************************/
/*								PHYS-619 Project							*/
/*	  		Hysteretic optimization for Sherrington-Kirkpatrick model		*/
/****************************************************************************/

// glassSK.c -- v.1.0 -- 04/12/2015 -- Longfei Fan

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include "ACD.h"
#include "r1279.h"

/****************************************************************************/
#define PI 3.14159265359

double gauss(){
	// Gaussian number generator: <x> = 0, sigma = 1

    double u1, u2, x;
   	u1 = r1279();
   	u2 = r1279();
	x = sqrt(-2*log(u2))*cos(2*PI*u1);
	return x;
}

double rand_gamma(){
	// Return a random number in [0.8, 1.0]

	double g;
	g = 0.8 + 0.2 * r1279();
	return g;
}

/****************************************************************************/
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

	sys.H = 0;
	update_sys(&sys);
	identify_unstable(&sys);

	return sys;
}

void free_J(GLASS_SK *sys){
	// Free the memory space allocated for sys.J

	int i;
	for (i=0; i < sys->N; i++)
		free(sys->J[i]);   
	free(sys->J);   
}

/****************************************************************************/
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

/****************************************************************************/
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

/****************************************************************************/
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

/****************************************************************************/
int quench(GLASS_SK *sys){
	// Indentify all the unstable spins, then randomly flip one of them.
	// Repeat untill all the spins are stable.
	// Return a flag to indicate whether any bit flips happen or not.

	int s, flag = 0;	/* flag = 0 indicating no flips happen */
	identify_unstable(sys);
	if(sys->unstable_num > 0)
		flag = 1;		/* flag = 1 indicating at least one flip happens */
	while(sys->unstable_num > 0){
		s = ir1279()%sys->unstable_num;
		flip_spin(sys, sys->unstable[s]);
		identify_unstable(sys);
	}
	/* If a quench is applied, return 1, otherwise return 0 */
	return flag;
}

/****************************************************************************/
void decrease_H(GLASS_SK *sys, double delta){
	/* Decrease the external field by delta, and update the system */

	int i;
	sys->H -= delta;
	sys->energy += delta * sys->magnetization;
		for(i = 0; i < sys->N; i++)
		sys->h[i] -= delta * sys->xi[i];
}

/****************************************************************************/
int half_cycle(GLASS_SK *sys, double H1, double H2){
	// Quench the system from H1 to H2 with a step of h.
	// When it goes across 0, record the optimal energy and the configuration.
	// Return how many queches happens in a half cycle.

	int i, j, quench_time = 0;
	double delta;

	/* Quench at H1 */
	delta = H1 / 20.0;
	sys->H = H1;
	update_sys(sys);	/* Calibrate the status of the system */
	quench_time += quench(sys);
	for(i = 1; i < 20; i++){
		decrease_H(sys, delta);
		quench_time += quench(sys);
	}

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

	/* Quench from 0 to H2 */
	delta = - H2 / 20.0;
	for(i = 0; i < 20; i++){
		decrease_H(sys, delta);
		quench_time += quench(sys);
	}

	return quench_time;
}

/****************************************************************************/
int ac_demag(GLASS_SK *sys, double H){
	// AC demagnetization starting from H to 0.
	// Return the number of half cycles in the whole procedure.

	int i, j, quench_time, cycle_time = 0 ;
	double h1, h2;

	/* Repeat cycles until no more quech is needed */
	h2 = H;
	do{
		h1 = h2;
		h2 = - rand_gamma() * h1;
		quench_time = half_cycle(sys, h1, h2);
		cycle_time += 1;
	}while(quench_time > 0);

	/* Bring the system back to H = 0 */
	sys->H = 0;
	update_sys(sys);
	identify_unstable(sys);
	/* Calculate the magnetization with no xi[i] factors */
	sys->magnetization = 0;
	for(i = 0; i < sys->N; i++)
		sys->magnetization += sys->sigma[i];

	return cycle_time;
}

/****************************************************************************/
void shake(GLASS_SK *sys, double Hs){
	// Shake the system obtained from a previous ac demagnetizaion.
	// Firstly generate a new list of sys.xi[]
	// Secondly apply another ac demagnetization procedure as Hs.

	int i, j;

	/* Generate a new list of sys.xi[] */
	for(i = 0; i < sys->N; i++)
		sys.xi[i] = ir1279()%2 * 2 - 1;
}

/****************************************************************************/
void print_system_status(GLASS_SK *sys){
	// Print out the current status of the system

	int i, j;
	printf("Size\tExternal Field\n");
	printf("%d\t\t%f\n", sys->N, sys->H);
	printf("sigma\txi\th\n");
	for(i = 0; i <sys->N; i++)
		printf("%d\t%d\t%f\n", sys->sigma[i], sys->xi[i], sys->h[i]);

	printf("\nJ[i][j]:\n");
	for(i = 0; i < sys->N; i++){
		for(j = 0; j < sys->N; j++)
			printf("%f\t", sys->J[i][j]);
		printf("\n");	
	}

	printf("\nEneryg\t\tMagnetization\n");
	printf("%f\t%f\n\n", sys->energy/sys->N, sys->magnetization/sys->N);
	printf("\nThe optimal energy:%f\n\n", sys->energy_stable/sys->N);

	for(i = 0; i < sys->N; i++)
		printf("%4d\t%f\n", sys->sigma[i], sys->h[i]);

	printf("\nUnstable spins:\n");
	for(i = 0; i < sys->N; i++)
		printf("%d\n", sys->unstable[i]);

	printf("Number of unstable spins: %d\n\n", sys->unstable_num);
}
