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
#include "omp.h"
#include "r1279.h"
#include "HO.h"

#define SAMPLE 32
#define H0 1.6
#define SHAKES 1000
#define HS 0.7

long seedgen(void);

int main(){

	long seed;
	seed = seedgen() + omp_get_thread_num();
	setr1279(seed);

	int i, j;
	double e_s = 0, e2_s = 0, m_s = 0, m2_s = 0;
	double e_std, m_std;

	FILE *fp1 = fopen("2048.dat", "at");
	fprintf(fp1, "# Energy\tThread - (Shake %d)\n", SHAKES);

	// omp_set_num_threads(4);

	#pragma omp parallel
	{	
		#pragma omp for
		for(i = 0; i < SAMPLE; i++){
			
			double e, e2, m, m2;

			GLASS_SK sys;
			sys = init_sys();		/* Initialize one instance */
			ac_demag(&sys, H0);		/* Apply ac demagniztion procedure */
			for(j = 0; j < SHAKES; j++)		/* Shake the systems */	
				shake(&sys, HS);

			e = sys.energy_stable/sys.N;	/* Output the resutls */
			e2 = pow(e, 2);
			// m = fabs(sys.magnetization/sys.N);
			// m2 = pow(m, 2);
			fprintf(fp1, "%.6f\t%3d\n", e, omp_get_thread_num());
			
			e_s += e;		/* Summation */
			e2_s += e2;
			// m_s += m;
			// m2_s += m2;
			
			free_J(&sys);	/* Free the space */
		}
	}
	fclose(fp1);

	e_s /= SAMPLE;	/* Averaging */
	e2_s /= SAMPLE;
	e_std = sqrt(e2_s - pow(e_s, 2)) * sqrt(SAMPLE/(SAMPLE-1.));

	FILE *fp2 = fopen("2048ave.dat", "at");
	fprintf(fp2, "# SIZE\tSample\tShake\tEn_ave\t\tEn_std\n");
	fprintf(fp2, "%4d\t%4d\t%4d\t%.6f\t%.6f\n", SIZE, SAMPLE, SHAKES, e_s, e_std);
	fclose(fp2);

	return 0;
}
