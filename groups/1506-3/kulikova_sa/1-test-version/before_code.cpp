#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <omp.h>
#include <random>

void NonlinearConjugateGradient(double ** A, double * b, double * x, int N);

//argv[1] - количество потоков, argv[2] - имя входного файла, argv[3] - имя выходного файла
int main(int argc, char * argv[]) {
	int num_threads = 1;
	if (argc > 1)
		num_threads = atoi(argv[1]);

	int N;
	double **A, *b, *x;

	freopen(argv[2], "rb", stdin);
	freopen(argv[3], "wb", stdout);

	fread(&N, sizeof(N), 1, stdin);

	A = new double*[N];
	for (int i = 0; i < N; i++)
		A[i] = new double[N];
	b = new double[N];
	x = new double[N];

	fread(A, sizeof(**A), N * N, stdin);
	fread(b, sizeof(*b), N, stdin);

	omp_set_num_threads(num_threads);

	double time = omp_get_wtime();
	NonlinearConjugateGradient(A, b, x, N);
	time = omp_get_wtime() - time;

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(x, sizeof(*x), N, stdout);

	/*
	for (int i = 0; i < N; i++)
		delete[] A[i];
	delete[] A;
	delete[] b;
	delete[] x;
	*/

	return 0;
}