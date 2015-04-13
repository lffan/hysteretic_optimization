/********************************************************************/
/*						PHYS-619 Project							*/
/*	  Hysteretic optimization for Sherrington-Kirkpatrick model		*/
/********************************************************************/

// glassSK.h -- v.1.0 -- 04/12/2015 -- Longfei Fan

# define SIZE 2048	/* number of spins */

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

	int unstable[SIZE];		/* list of unstable spins' indics */
	int unstable_num;		/* number of unstable spins*/
}GLASS_SK;

// Gaussian number generator: <x> = 0, sigma = 1
double gauss();

// Return a random number in [0.8, 1.0]
double rand_gamma();

// Initialize the Sherrington-Kirkpatrick spin glass system
GLASS_SK init_sys();

// Free the memory space allocated for sys.J
void free_J(GLASS_SK *);

// Update the current properties of system
void update_sys(GLASS_SK *sys);

// Identify all unstable spins and store the indics and numbers
void identify_unstable(GLASS_SK *);

// Flip an unstable spin, and update the properties of system
void flip_spin(GLASS_SK *, int);

// Flip unstable spins until all spins are stable
// Return 1 or 0 to indicate whether a quench is applied or not
int quench(GLASS_SK *);

// Decrease the external field and update the properties of system
void decrease_H(GLASS_SK *, double);

// Quech a system form H to -g*H step by step.
// Return the times of quench in this half cycle.
int half_cycle(GLASS_SK *, double, double);

// AC demagnetization for H to 0.
// Return the total numbers of half cycle.
int ac_demag(GLASS_SK *, double);

// Print the properties of the current system.
void print_system_status(GLASS_SK *);