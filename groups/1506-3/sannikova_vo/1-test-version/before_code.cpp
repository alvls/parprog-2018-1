//#define _CRT_SECURE_NO_WARNINGS
//#include <cstdio>
//#include <omp.h>
//#include <random>
//#include <vector>
//
//using namespace std;
//
//
//void qSort(vector<double>* vec);
//void qSort(double* arr, int size);
//
//
//int main(int argc, char * argv[])
//{
//	int num_threads = 1;
//	if (argc > 1)
//		num_threads = atoi(argv[1]);
//
//	vector<double> vec;
//
//
//	//vec.resize();
//
//
//	double ttime;
//	int size;
//	double *arr;
//
//	freopen("vec.in", "rb", stdin);
//	freopen("vec.out", "wb", stdout);
//
//	fread(&ttime, sizeof(ttime), 1, stdin);
//	fread(&size, sizeof(size), 1, stdin);
//	arr = new double[size];
//	fread(arr, sizeof(*arr), size, stdin);
//
//
//	//fread(&vec[0], (size)*sizeof(double), 1, stdin); чтение в вектор
//	for (int i = 0; i < size; i++) {
//		fread(&vec[i], sizeof(double), 1, stdin);
//	}
//	
//	double time = omp_get_wtime();
//	qSort(arr, size);
//	//omp_set_num_threads(num_threads);
//	//double time = omp_get_wtime();
//	qSort(&vec);
//
//	time = omp_get_wtime() - time;
//	
//	fwrite(&time, sizeof(time), 1, stdout);
//	fwrite(&size, sizeof(size), 1, stdout);
//	fwrite(arr, sizeof(*arr), size, stdout);
//
//	//fwrite(&vec, (size) * sizeof(double), size, stdout);
//	for (int i = 0; i < size; i++) {
//		fwrite(&vec[i], sizeof(double), 1, stdin);
//	}
//
//	return 0;
//}
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

int main(int argc, char * argv[])
{
	if (argc != 3) {
		std::cout << "You input incorrect number of arguments. Input 'solver input.bin output.bin'" << std::endl;
		return 1;
	}

	int size;
	int* arr;
	double _time;


	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wb", stdout);

	fread(&_time, sizeof(_time), 1, stdin); //template for the future, isn't use now
	fread(&size, sizeof(size), 1, stdin);
	vector <double> vec(size);
	for (int i = 0; i < size; ++i) {
		fread(&vec[i], sizeof(double), 1, stdin);
	}
	double time = omp_get_wtime();
	qSort(&vec);
	time = omp_get_wtime() - time;

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);

	for (int i = 0; i < size; ++i) {
		fwrite(&vec[i], sizeof(double), 1, stdout);
	}
	return 0;
}