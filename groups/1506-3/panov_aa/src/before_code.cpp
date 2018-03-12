#include <omp.h>
#include <string>
#include<iostream>
using std::string;
void MatrMatrMult(double * A, double * B, double * C, int N);

int main(int argc, char * argv[])//читает из бинарного файла, запускает программу, пишет в бинарный файл
{
	int num_threads = 1;
	string name = "matr";
	string number = "";
	string extensionIn = ".in";
	string extensionOut = ".out";
	if (argc > 1)
	{
		num_threads = atoi(argv[1]);
		if (argc > 2)
		{
			number = argv[2];
		}
	}

	int N;
	double *A, *B, *C;

	freopen((name + number + extensionIn).c_str(), "rb", stdin);
	freopen((name + number + extensionOut).c_str(), "wb", stdout);
	fread(&N, sizeof(N), 1, stdin);
	A = new double[N * N];
	B = new double[N * N];
	C = new double[N * N];
	fread(A, sizeof(*A), N * N, stdin);
	fread(B, sizeof(*B), N * N, stdin);
	omp_set_num_threads(num_threads);
	double time = omp_get_wtime();
	MatrMatrMult(A, B, C, N);
	time = omp_get_wtime() - time;
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(C, sizeof(*C), N * N, stdout);

	return 0;
}