#define SIZE 16
#define H1 0.0

typedef struct{
	int N;
	int sigma[SIZE];
	double ** J;
	double energy;
	double magnetization;

	double H;
	int xi[SIZE];
	double h[SIZE];

	int unstable[SIZE];
	int unstable_num;
}GLASS_SK;

GLASS_SK init_sys();
void identify_unstable(GLASS_SK *);
void update_spin(GLASS_SK *sys, int s);
void quench(GLASS_SK *sys);
void ac_demag(GLASS_SK *sys);
void print_system_status(GLASS_SK *sys);