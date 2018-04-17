#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <random>
#include <ctime>
#include <omp.h>
#include <iostream>
#include <vector>
using namespace std;

void qSort(double* arr, int size);
void qSort(vector<double>* vec);
void qSort_array_recursion(double* arr, int size);
void QuickSort_OpenMP(double items[], int size);

int main(int argc, char * argv[])
{
	if (argc != 3) {
		std::cout << "You input incorrect number of arguments. Input 'solver input.bin output.bin'" << std::endl;
		return 1;
	}

	int size;
	//double* arr;
	double _time;


	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wb", stdout);

	fread(&_time, sizeof(_time), 1, stdin); //template for the future, isn't use now
	fread(&size, sizeof(size), 1, stdin);
	
	double *arr = new double[size];

	//vector <double> vec(size);
	for (int i = 0; i < size; ++i) {
		fread(&arr[i], sizeof(double), 1, stdin);
		//fread(&vec[i], sizeof(double), 1, stdin);
	}
	double time = omp_get_wtime();
	//qSort_array_recursion(arr, size);
	QuickSort_OpenMP(arr, size);
	//qSort(&vec);
	time = omp_get_wtime() - time;
	
	printf("Linear time: %f\n", time);

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);

	for (int i = 0; i < size; ++i) {
		fwrite(&arr[i], sizeof(double), 1, stdout);
	}
	return 0;
}