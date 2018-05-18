#include <cstdio> 
#include <cstring>
#include <omp.h> 
#include <random>
#include "Func.h"
#include "sol.h"

int main(int argc, char * argv[]) {
	int num_threads = 1;
	if (argc > 1) num_threads = atoi(argv[1]);
	int size = 0;

	double integral;

	freopen(argv[2], "rb", stdin);
	freopen(strcat(argv[2],".ans"), "wb", stdout);
	fread(&size, sizeof(int), 1, stdin);

	double* buf = new double(size);

	double confines[4];

	Func* fun = new Func(size);
	for (int i = 0; i < 7; i++) {
		fread(buf, sizeof(*buf), size, stdin);
		switch (i) {
		case 0: {
			fun->SetCoeffs(buf);
			break;
		}
		case 1: {
			fun->SetXindexs(buf);
			break;
		}
		case 2: {
			fun->SetYindexs(buf);
			break;
		}
		case 3: {
			fun->SetXcos(buf);
			break;
		}
		case 4: {
			fun->SetYcos(buf);
			break;
		}
		case 5: {
			fun->SetXsin(buf);
			break;
		}
		case 6: {
			fun->SetYsin(buf);
			break;
		}
		default:
			break;
		}
	}

	fread(confines, sizeof(*confines), 4, stdin);

	//omp_set_num_threads(num_threads);
	//double time = omp_get_wtime();
	integral = TIntegral(fun, confines[0], confines[1], confines[2], confines[3], 0.01);
	//time = omp_get_wtime() - time;
	//fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&integral, sizeof(double), 1, stdout);

	system ("pause");
	return 0;
}
