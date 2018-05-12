
#include "stdafx.h"
#include <fstream>
#include <random> 
#include <ctime> 
#include <chrono>
#include <omp.h>
#include <cstdio>
#include <string>

using namespace std;
int n_tests[] = { 1000, 5000, 10000, 20000, 50000, 100000, 150000, 200000, 250000, 300000, 400000, 500000, 1000000, 5000000, 10000000, 15000000, 20000000, 30000000, 40000000, 50000000 };

int main(int argc, char * argv[])
{
	string nameFile;
	int size, n = 20;

	for (int i = 1; i <= n; i++)
	{
		double* array;
		nameFile = to_string((long long)i);
		FILE* fArray = fopen(("./tests/" + nameFile).c_str(), "wb");

		default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
		uniform_real_distribution <double> distribution(-1e4, 1e4);
		size = n_tests[i - 1];

		if (argc > 1)
			size = n_tests[atoi(argv[1])];

		fwrite(&size, sizeof(size), 1, fArray);

		array = new double[size];

		for (int i = 0; i < size; i++)
			array[i] = distribution(generator);

		fwrite(array, sizeof(*array), size, fArray);

		fclose(fArray);

		delete[] array;
	}

	return 0;
}