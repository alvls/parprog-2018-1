#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <omp.h>

void LsdRadixSort(double* arr, const size_t arr_size);

int main(int argc, char** argv) {
	if (argc != 4) {
		std::cout
			<< "Solver\n"
			<< "Usage: [.exe name] [input file] [output file] [number of threads]\n"
			<< "Note that the number of threads MUST be divisible by 2."
			<< std::endl;
		
		return 1;
	}

	int number_of_threads = atoi(argv[3]);

	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wb", stdout);

	double time;
	int arr_size;
	double* arr;

	fread(&time, sizeof(time), 1, stdin);
	fread(&arr_size, sizeof(arr_size), 1, stdin);

	arr = new double[arr_size];

	fread(arr, sizeof(arr), arr_size, stdin);	

	omp_set_num_threads(number_of_threads);

	double elapsed_time = omp_get_wtime();
	LsdRadixSort(arr, arr_size);
	elapsed_time = omp_get_wtime() - elapsed_time;

	fwrite(&elapsed_time, sizeof(elapsed_time), 1, stdout);
	fwrite(&arr_size, sizeof(arr_size), 1, stdout);
	fwrite(arr, sizeof(arr), arr_size, stdout);

	delete[] arr;

	return 0;
}