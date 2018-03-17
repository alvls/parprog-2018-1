#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <omp.h>
#include <random>


void ShellSort(double * A, int size);


int main(int argc, char * argv[])
{
	int num_threads = 1;
	if (argc > 1)
		num_threads = atoi(argv[1]);
	int size;
	double *A;
	FILE *input_file = fopen("../massiv.in", "rb");
	FILE *output_file = fopen("../massiv.out", "wb");
	fread(&size, sizeof(size), 1, input_file);


	A = new double[size];

	fread(A, sizeof(*A), size, input_file);

	omp_set_num_threads(num_threads);
	double time = omp_get_wtime();
	ShellSort(A, size);

	time = omp_get_wtime() - time;
	fwrite(&time, sizeof(time), 1, output_file);
	fwrite(&size, sizeof(size), 1, output_file);
	fwrite(A, sizeof(*A), size, output_file);

	fclose(input_file);
	fclose(output_file);
	return 0;
}