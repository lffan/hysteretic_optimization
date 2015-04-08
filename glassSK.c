#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include "glassSK.h"
#include "r1279.h"

GLASS create_spins(){
	/* Create spin glass */
	int i, j;

	GLASS sys;
	sys.L = SIZE;
	sys.N = SIZE*SIZE;
	sys.temperature = 0;
	
	/* Initialize the neighbor table */
	for(i = 0; i < sys.N; i++){
		sys.spins[i] = 1;
		sys.nb[i][0] = (i+sys.L-1)%sys.L + (int)(i/sys.L)*sys.L;
		sys.nb[i][1] = (i+1)%sys.L + (int)(i/sys.L)*sys.L;
		sys.nb[i][2] = (i-sys.L+sys.N)%sys.N;
		sys.nb[i][3] = (i+sys.L)%sys.N;
	}
	/* Initialize the J table */
	for(i = 0; i < sys.N; i++){
		if(r1279() <= 0.5)
			sys.J[i][0] = sys.J[sys.nb[i][0]][1] = 1;
		else
			sys.J[i][0] = sys.J[sys.nb[i][0]][1] = -1;
		if(r1279() <= 0.5)
			sys.J[i][2] = sys.J[sys.nb[i][2]][3] = 1;
		else
			sys.J[i][2] = sys.J[sys.nb[i][2]][3] = -1;
	}


	/* Initial energy and magnetization */
	sys.magnetization = sys.N;
	sys.energy = 0;
	for(i = 0; i < sys.N; i++){
		sys.energy += sys.J[i][0] * sys.spins[i] * sys.spins[sys.nb[i][0]];
		sys.energy += sys.J[i][2] * sys.spins[i] * sys.spins[sys.nb[i][2]];
	}
	
	return sys;
}

void update_spin(GLASS *sys){
	/* update one spin randomly */
	int s = ir1279range(0, sys->N - 1);
	int delta = 0;

	int i, j;
	for(i = 0; i < 4; i++){
		delta += 2*sys->J[s][i]*sys->spins[s]*sys->spins[sys->nb[s][i]];
	}
	if(r1279() < exp(-1.0*delta/sys->temperature)){
		sys->spins[s] = - sys->spins[s];
		sys->energy += delta;
		sys->magnetization += 2 * sys->spins[s];
	}
}

void sweep(GLASS *sys){
	/* update all the spins */
	int i;
	for(i = 0; i < sys->N; i++)
		update_spin(sys);
}