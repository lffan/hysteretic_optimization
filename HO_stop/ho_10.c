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

#define INSTANCES 1000
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
	double e_std, m_std;

	FILE *fp1 = fopen("HO_10_2048.dat", "w");
	fprintf(fp1, "# Energy\ttMagnetic\n");

	for(i = 0; i < INSTANCES; i++){
		sys = init_sys();		/* Initialize one instance */
		ac_demag(&sys, H0);		/* Apply ac demagniztion procedure */
		for(j = 0; j < SHAKES; j++)		/* Shake the systems */	
			shake(&sys, HS);

		e = sys.energy_stable/sys.N;	/* Output the resutls */
		e2 = pow(e, 2);
		m = fabs(sys.magnetization/sys.N);
		m2 = pow(m, 2);
		fprintf(fp1, "%.6f\t%.6f\n", e, m);
		
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
	e_std = sqrt(e2_s - pow(e_s, 2)) * sqrt(INSTANCES/(INSTANCES-1.));
	m_std = sqrt(m2_s - pow(m_s, 2)) * sqrt(INSTANCES/(INSTANCES-1.));

	FILE *fp2 = fopen("HO_10_2048_ave.dat", "w");
	fprintf(fp2, "# SIZE\tInsts\tEn_ave\t\tEn_std\t\tMag_ave\t\tMag_std\n");
	fprintf(fp2, "%4d\t%5d\t%.6f\t%.6f\t%.6f\t%.6f\n", SIZE, INSTANCES, e_s, e_std, m_s, m_std);
	fclose(fp2);

	return 0;
}
