/* Generating Gaussian distribution */

#include <stdio.h>
#include <math.h>
#include "r1279.h"

#define PI 3.14159265359

double gauss(){
	/* Gaussian number generator: <x> = 0, sigma = 1 */
    double u1, u2, x;
   	u1 = r1279();
   	u2 = r1279();
	x = sqrt(-2*log(u2))*cos(2*PI*u1);
	return x;
}
