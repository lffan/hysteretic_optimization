# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "r1279.h"
# include "glassSK.h"

# define INSTANCES 1
# define H0 1.6

long seedgen(void);

int main(){

	long seed;
	seed = seedgen();
	setr1279(seed);

	FILE *fp1 = fopen("en_mag.dat", "w");
	FILE *fp2 = fopen("en_mag_ave.dat", "w");

	int i, times;
	double cycle_time = 0;
	double e, e2, m, m2;
	double e_s = 0, e2_s = 0, m_s = 0, m2_s = 0;

	fprintf(fp1, "# Energy\tEnergy^2\tCycles\n");
	for(i = 0; i < INSTANCES; i++){
		GLASS_SK sys;
		sys = init_sys();
		times = ac_demag(&sys, H0);
		cycle_time += times;
		e = sys.energy_stable/sys.N;
		e2 = pow(e, 2);
		// m = fabs(sys.magnetization/sys.N);
		// m2 = pow(m, 2);
		fprintf(fp1, "%.6f\t%.6f\t%d\n", e, e2, times);
		e_s += e;
		e2_s += e2;
		// m_s += m;
		// m2_s += m2;
	}
	fclose(fp1);
	e_s /= INSTANCES;
	e2_s /= INSTANCES;
	cycle_time /= INSTANCES;
	// m_s /= INSTANCES;
	// m2_s /= INSTANCES;
	fprintf(fp2, "# En_Ave\tEn2_Ave\t\tCycles_Ave\n");
	fprintf(fp2, "%.6f\t%.6f\t%.6f\n", e_s, e2_s, cycle_time);
	fclose(fp2);

	return 0;
}