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

	FILE *fp1 = fopen("ACD.dat", "w");
	fprintf(fp1, "# Energy\tEnergy^2\tMagnetic\tMagnet^2\tCycles\n");

	for(i = 0; i < INSTANCES; i++){
		sys = init_sys();		/* Initialize one instance */
		times = ac_demag(&sys, H0);		/* Apply ac demagniztion procedure */
		
		e = sys.energy_stable/sys.N;	/* Output the resutls */
		e2 = pow(e, 2);
		m = fabs(sys.magnetization/sys.N);
		m2 = pow(m, 2);
		fprintf(fp1, "%.6f\t%.6f\t%.6f\t%.6f\t%d\n", e, e2, m, m2, times);
		
		cycle += times;		/* Averaging */
		e_s += e;
		e2_s += e2;
		m_s += m;
		m2_s += m2;
		
		free_J(&sys);		/* Free the space */
	}
	fclose(fp1);

	e_s /= INSTANCES;
	e2_s /= INSTANCES;
	cycle /= INSTANCES;
	m_s /= INSTANCES;
	m2_s /= INSTANCES;

	FILE *fp2 = fopen("ACD_ave.dat", "w");
	fprintf(fp2, "# En_Ave\tEn2_Ave\t\tMag_Ave\t\tMag2_Ave\tCycles_Ave\n");
	fprintf(fp2, "%.6f\t%.6f\t%.6f\t%.6f\t%f\n", e_s, e2_s, m_s, m2_s, cycle);
	fclose(fp2);

	return 0;
}
