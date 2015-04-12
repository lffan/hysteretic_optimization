#define SIZE 1000

typedef struct{
	int N;
	int sigma[SIZE];
	int sigma_best[SIZE];
	double ** J;
	double energy;
	double energy_stable;
	double magnetization;

	double H;
	int xi[SIZE];
	double h[SIZE];

	int unstable[SIZE];
	int unstable_num;
}GLASS_SK;

GLASS_SK init_sys();
void identify_unstable(GLASS_SK *);
void update_sys(GLASS_SK *sys);
void flip_spin(GLASS_SK *, int);
int quench(GLASS_SK *);
int half_cycle(GLASS_SK *, double, double);
double rand_gamma();
int ac_demag(GLASS_SK *, double);
void print_system_status(GLASS_SK *);