#define SIZE 8
#define H1 6

typedef struct{
	int N;
	int sigma[SIZE];
	double J[SIZE][SIZE];
	double energy;
	double magnetization;

	double H;
	int xi[SIZE];
	double h[SIZE];
}GLASS_SK;

GLASS_SK init_sys();