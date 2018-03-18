#include <cstdio> 
#include <omp.h> 
#include <random>
#include "Func.h"

double TIntegral(Func* fun, double start, double finish, double accuracy, int parts = 200);

int main(int argc, char * argv[]) {
	int num_threads = 1;
	if (argc > 1) num_threads = atoi(argv[1]);
	int size;

	double integral = 0.0;

	freopen("matr.in", "rb", stdin);
	freopen("matr.out", "wb", stdout);
	fread(&size, sizeof(size), 1, stdin);

	double* buf = new double(size);

	double start = 0.0;
	double finish = 4.0;

	Func* fun = new Func(size);
	for (int i = 0; i < 7; i++) {
		fread(buf, sizeof(*buf), size, stdin);
		switch (i) {
		case 0: fun->SetCoeffs(buf);
		case 1: fun->SetXindexs(buf);
		case 2: fun->SetYindexs(buf);
		case 3: fun->SetXcos(buf);
		case 4: fun->SetYcos(buf);
		case 5: fun->SetXsin(buf);
		case 6: fun->SetYsin(buf);
		default:
			break;
		}
	}


	fread(&start, sizeof(start), 1, stdin);
	fread(&finish, sizeof(finish), 1, stdin);

	omp_set_num_threads(num_threads);
	double time = omp_get_wtime();
	
	integral = TIntegral(fun, start, finish, 0.01);

	time = omp_get_wtime() - time;
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&integral, sizeof(integral), 1, stdout);
	return 0;
}
