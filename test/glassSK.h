#define SIZE 8

typedef struct{
	int N;
	double spins[SIZE];
	double J[SIZE][SIZE];
	double xi[SIZE];
	double energy;
	double magnetization;
}GLASS;

GLASS create_spins();
void update_spin(GLASS *);
void sweep(GLASS *);