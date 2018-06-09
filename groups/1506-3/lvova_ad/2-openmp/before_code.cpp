#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <omp.h>
#include <random>
#include <iostream>

void shell_sort_with_a_shift(double* array, int iteration, int length);


//void shell_parallel_tbb_sort(double* array, int length, int n_threads);
void shell_parallel_openmp_sort(double* array, int length, int n_threads);

int main(int argc, char * argv[])
{
	int num_threads = 1;
	if (argc >= 1)
		num_threads = atoi(argv[1]);
	int size;
	double *A;
	FILE *input_file = fopen("../massiv.in", "rb");
	FILE *output_file = fopen("../massiv.out", "wb");
	fread(&size, sizeof(size), 1, input_file);

	A = new double[size];

	fread(A, sizeof(*A), size, input_file);
   
     if (size <= 100) {
        std::cout << std::endl;
        for (int i = 0; i < size; i++)
            std::cout << A[i] << " ";
    }

	double time = omp_get_wtime();
    if (num_threads > 1)
        shell_parallel_openmp_sort(A, size, num_threads);
    else
        shell_sort_with_a_shift(A, 0, size);

	time = omp_get_wtime() - time;

    if (size <= 100)
    {
        std::cout << std::endl << std::endl;
        for (int i = 0; i < size; i++)
            std::cout << A[i] << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl << "time = " << time << std::endl;

	fwrite(&time, sizeof(time), 1, output_file);
	fwrite(&size, sizeof(size), 1, output_file);
	fwrite(A, sizeof(*A), size, output_file);

	fclose(input_file);
	fclose(output_file);
	return 0;
}
