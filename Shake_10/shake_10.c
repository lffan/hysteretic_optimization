/****************************************************************************/
/*								PHYS-619 Project							*/
/*	  		Hysteretic optimization for Sherrington-Kirkpatrick model		*/
/****************************************************************************/

// Apply hysteretic optimation method to find the ground state energy of
// the Sherrington-Kirkpatrick model. Output the optimal energy, and the
// residue magnetization.

// v.1.0 -- 04/12/2015 -- Longfei Fan

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "r1279.h"
#include "HO.h"

#define INSTANCES 250
#define H0 1.6
#define SHAKES 10
#define HS 0.7

long seedgen(void);

int main(){

	long seed;
	seed = seedgen();
	setr1279(seed);

	int i, j;
	GLASS_SK sys;
	double cycle = 0;
	double e, e2, m, m2;
	double e_s = 0, e2_s = 0, m_s = 0, m2_s = 0;

	FILE *fp1 = fopen("shake_10_2048.dat", "at");
	fprintf(fp1, "# Energy\tEnergy^2\tMagnetic\tMagnet^2\n");

	for(i = 0; i < INSTANCES; i++){
		sys = init_sys();		/* Initialize one instance */
		ac_demag(&sys, H0);		/* Apply ac demagniztion procedure */
		for(j = 0; j < SHAKES; j++)		/* Shake the systems */	
			shake(&sys, HS);

		e = sys.energy_stable/sys.N;	/* Output the resutls */
		e2 = pow(e, 2);
		m = fabs(sys.magnetization/sys.N);
		m2 = pow(m, 2);
		fprintf(fp1, "%.6f\t%.6f\t%.6f\t%.6f\n", e, e2, m, m2);
		
		e_s += e;		/* Summation */
		e2_s += e2;
		m_s += m;
		m2_s += m2;
		
		free_J(&sys);	/* Free the space */
	}
	fclose(fp1);

	e_s /= INSTANCES;	/* Averaging */
	e2_s /= INSTANCES;
	cycle /= INSTANCES;
	m_s /= INSTANCES;
	m2_s /= INSTANCES;

	FILE *fp2 = fopen("shake_10_2048_ave.dat", "at");
	fprintf(fp2, "%4d\t%.6f\t%.6f\t%.6f\t%.6f\n", SIZE, e_s, e2_s, m_s, m2_s);
	fclose(fp2);

	return 0;
}
