/* Generating Gaussian distribution */

#include <stdio.h>
#include <math.h>
#include "r1279.h"

#define PI 3.14159265359

double gauss(){
	/* Gaussian number generator: <x> = 0, sigma = 1 */
    double u1, u2, x;
    do{
    	u1 = r1279();
    	u2 = r1279();
    }while(u1 == 0.0 || u2 == 0.0);	
	x = sqrt(-2*log(u2))*cos(2*PI*u1);
	return x;
}