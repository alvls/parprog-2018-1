#define  _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include <fstream>
#include <random> 
#include <ctime> 
#include <chrono>
#include <omp.h>
#include <cstdio>
#include <string>

using namespace std;
int n_tests[] = { 40, 50, 60, 70, 80, 90, 100, 500, 1000, 5000, 10000, 20000, 50000, 100000, 150000, 200000, 250000, 300000, 400000, 500000, 1000000, 5000000, 10000000};

int _main(int argc, char * argv[])
{
	int n = 1, i = 24;
	double* array;
	string nameFile = to_string((long long)i);
	FILE* fArray = fopen(("./tests/" + nameFile).c_str(), "wb");

	// создаём генератор случайных чисел с seed равным количеству времени с начала эпохи   
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	// создаём равномерное распределение случайной величины типа double в диапазоне    
	//   [-10000, 10000]   
	uniform_real_distribution <double> distribution(-1e4, 1e4);
	int size = n_tests[n - 1];
	// если передали номер теста в аргументах командной строки, то берём размер из n_tests   
	if (argc > 1)
		size = n_tests[atoi(argv[1])];
	// записываем в бинарном виде размерность матриц   
	fwrite(&size, sizeof(size), 1, fArray);

	array = new double[size];

	for (int i = 0; i < size; i++)
		array[i] = distribution(generator);

	fwrite(array, sizeof(*array), size, fArray);

	fclose(fArray);

	delete[] array;
	return 0;
}
