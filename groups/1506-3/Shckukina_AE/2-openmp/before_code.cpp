#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio> 
#include <random>
#include <omp.h>


using namespace std;

void quicksort(double* arr, int size);
void quicksort_omp(double arr[], int first, int last);

int main(int argc, char * argv[])
{
	if (argc != 3) {
		std::cout << "Error! You should input 'solver input.bin output.bin'" << std::endl;
		return 1;
	}

	int size;
	double* array;
	double _time;


	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wb", stdout);

	fread(&_time, sizeof(_time), 1, stdin);
	fread(&size, sizeof(size), 1, stdin);

	array = new double[size];
	fread(array, sizeof(*array), size, stdin);

	double time = omp_get_wtime();
	//quicksort(array, size);
	quicksort_omp(array, 0, size - 1);
	time = omp_get_wtime() - time;

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);

	fwrite(array, sizeof(*array), size, stdout);

	return 0;
}