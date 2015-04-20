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

#define SAMPLE 1000
#define SHAKES 10
#define H0 1.6
#define HS 0.7

long seedgen(void);

int main(){
	
	long seed;
	seed = seedgen();
	setr1279(seed);

	double e_s = 0, e2_s = 0;
	double e_std, m_std;

	FILE *fp1 = fopen("1024_1000.dat", "at");
	fprintf(fp1, "Hysteresis Optimation of SK Spin Glass - Shake: %d\n\n", SHAKES);
	fprintf(fp1, "Size: %d\tSamples: %d\n\n", SIZE, SAMPLE);
	fprintf(fp1, "# Energy	Core\n");
	
	int i;	/* i is shared by threads */
	#pragma omp parallel
	{	
		#pragma omp for
		for(i = 0; i < SAMPLE; i++){

			double e, e2, m, m2;

			GLASS_SK sys;		/* sys is private for each thread */
			sys = init_sys();		/* Initialize one instance */
			ac_demag(&sys, H0);		/* Apply ac demagniztion procedure */
			
			int j;	/* j is private for each thread */
			for(j = 0; j < SHAKES; j++)		/* Shake the systems */	
				shake(&sys, HS);

			e = sys.energy_stable/sys.N;	/* Output the resutls */
			e2 = pow(e, 2);
			fprintf(fp1, "%.6f\t%d\n", e, omp_get_thread_num());
			
			e_s += e;		/* Summation */
			e2_s += e2;
			free_J(&sys);	/* Free the space */
		}
	}
	fclose(fp1);

	e_s /= SAMPLE;	/* Averaging */
	e2_s /= SAMPLE;
	e_std = sqrt(e2_s - pow(e_s, 2)) * sqrt(SAMPLE/(SAMPLE-1.));

	FILE *fp2 = fopen("1024_ave.dat", "at");
	fprintf(fp2, "# SIZE\tSamples\tEn_ave\t\tEn_std\t\tShakes\n");
	fprintf(fp2, "%4d\t%4d\t%.6f\t%.6f\t%4d\n", SIZE, SAMPLE, e_s, e_std, SHAKES);
	fclose(fp2);
	
	printf("Size: %d\tSamples: %d\tShakes: %d done!\n", SIZE, SAMPLE, SHAKES);

	return 0;
}
