#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <tbb/tbb.h>

void LsdRadixSort(double* arr, const size_t arr_size, int num_threads);

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout
			<< "Solver (TBB)\n"
			<< "Usage: [.exe name] [input file] [output file] [number of threads]\n"
			<< "Note that the number of threads MUST be divisible by 2."
			<< std::endl;
		
		return 1;
	}

	int number_of_threads = atoi(argv[3]) || 1;

	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wb", stdout);

	size_t arr_size;
	double* arr;

	fread(&arr_size, sizeof(arr_size), 1, stdin);

	arr = new double[arr_size];

	fread(arr, sizeof(arr), arr_size, stdin);

	tbb::tick_count time_start = tbb::tick_count::now();

	LsdRadixSort(arr, arr_size, number_of_threads);

	tbb::tick_count time_end = tbb::tick_count::now();
	const double elapsed_time = (time_end - time_start).seconds();

	fwrite(&elapsed_time, sizeof(elapsed_time), 1, stdout);
	fwrite(arr, sizeof(arr), arr_size, stdout);

	delete[] arr;

	return 0;
}