/********************************************************************/
/*						PHYS-619 Project							*/
/*	  Hysteretic optimization for Sherrington-Kirkpatrick model		*/
/********************************************************************/

// glassSK.h -- v.1.0 -- 04/12/2015 -- Longfei Fan

# define SIZE 2048	// Number of spins

typedef struct{
	// Sherrington-Kirkpatrick spin glass structure

	int N;					/* number of spins */
	int sigma[SIZE];		/* configuration of spins */
	int sigma_best[SIZE];	/* optimal configuration */
	double ** J;			/* interation fators */
	double energy;			/* system energy */
	double energy_stable;	/* optimal energy */
	double magnetization;	/* system magnetization */

	double H;			/* external field */
	int xi[SIZE];		/* direction of H for each spin */
	double h[SIZE];		/* local field for each spin */

	int unstable[SIZE];
	int unstable_num;
}GLASS_SK;

double gauss();
double rand_gamma();

GLASS_SK init_sys();

void identify_unstable(GLASS_SK *);
void update_sys(GLASS_SK *sys);
void flip_spin(GLASS_SK *, int);

int quench(GLASS_SK *);
int half_cycle(GLASS_SK *, double, double);
int ac_demag(GLASS_SK *, double);

void print_system_status(GLASS_SK *);