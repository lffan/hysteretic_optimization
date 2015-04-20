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

#define SAMPLE 1
#define H0 1.6

long seedgen(void);

int main(){

	long seed;
	seed = seedgen();
	setr1279(seed);

	GLASS_SK sys;
	sys = init_sys();
	ac_demag(&sys, H0);

	return 0;
}
