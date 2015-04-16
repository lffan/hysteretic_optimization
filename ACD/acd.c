// Apple ac demagnetization method to find the ground state 
// 		energy of the Sherrington-Kirkpatrick model.
// Output the optimal energy, the residue magnetization, and
// 		the cycle times of each instance.

// v.1.0 -- 04/12/2015 -- Longfei Fan

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "r1279.h"
#include "HO.h"

#define INSTANCES 1000
#define H0 1.6

long seedgen(void);

int main(){

	long seed;
	seed = seedgen();
	setr1279(seed);

	int i, times;
	GLASS_SK sys;
	double cycle = 0;
	double e, e2, m, m2;
	double e_s = 0, e2_s = 0, m_s = 0, m2_s = 0;
	double e_std, m_std;

	FILE *fp1 = fopen("acd_2048.dat", "w");
	fprintf(fp1, "# Energy\tMagnetic\tCycles\n");

	for(i = 0; i < INSTANCES; i++){
		sys = init_sys();		/* Initialize one instance */
		times = ac_demag(&sys, H0);		/* Apply ac demagniztion procedure */
		
		e = sys.energy_stable/sys.N;	/* Output the resutls */
		e2 = pow(e, 2);
		m = fabs(sys.magnetization/sys.N);
		m2 = pow(m, 2);
		fprintf(fp1, "%.6f\t%.6f\t%d\n", e, m, times);
		
		cycle += times;		/* Averaging */
		e_s += e;
		e2_s += e2;
		m_s += m;
		m2_s += m2;
		
		free_J(&sys);		/* Free the space */
	}
	fclose(fp1);

	cycle /= INSTANCES;
	e_s /= INSTANCES;
	e2_s /= INSTANCES;
	e_std = sqrt(e2_s - pow(e_s, 2)) * sqrt(INSTANCES/(INSTANCES-1.));
	m_s /= INSTANCES;
	m2_s /= INSTANCES;
	m_std = sqrt(m2_s - pow(m_s, 2)) * sqrt(INSTANCES/(INSTANCES-1.));

	FILE *fp2 = fopen("acd_N.dat", "at");
	// fprintf(fp2, "# SIZE\tInsts\tEn_ave\t\tEn_std\t\tMag_ave\t\tMag_std\t\tCycl_ave\n");
	fprintf(fp2, "%4d\t%5d\t%.6f\t%.6f\t%.6f\t%.6f\t%f\n", SIZE, INSTANCES, e_s, e_std, m_s, m_std, cycle);
	fclose(fp2);

	return 0;
}
