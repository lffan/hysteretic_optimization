#define SIZE 1024

typedef struct{
	int N;
	int sigma[SIZE];
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
void quench(GLASS_SK *);
void half_cycle(GLASS_SK *, double, double);
void ac_demag(GLASS_SK *, double);
void print_system_status(GLASS_SK *);