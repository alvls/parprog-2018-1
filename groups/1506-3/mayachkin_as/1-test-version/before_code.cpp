#include <cstdio>
#include <fstream>
#include <random>
#include <omp.h>
#include <string>
#include <iostream>

using namespace std;

void RadixSort(double* data, int dataLength);
void ParallelSort(double* data, int size, int pnum);
void TBBParallelSort(double *input, int size, int nThreads);

int main(int argc, char * argv[])
{
	string nameFile;
	int n = 20;
	int num_threads = 2;
	int size;

	if (argc > 1)
		num_threads = atoi(argv[1]);

	for (int i = 20; i <= n; i++)
	{
		nameFile = to_string((long long)i);
		FILE* fArray = fopen(("./tests/" + nameFile).c_str(), "rb");
		FILE* fRadixResult = fopen(("./tests/" + nameFile + ".ans").c_str(), "wb");
		FILE* fParallelResult = fopen(("./tests/" + nameFile + "_par.ans").c_str(), "wb");

		fread(&size, sizeof(size), 1, fArray);

		double *array = new double[size];
		fread(array, sizeof(*array), size, fArray);

		double* array2 = new double[size];

		for (int j = 0; j < size; j++)
		{
			array2[j] = array[j];
		}

		double time = omp_get_wtime();
		RadixSort(array, size);
		time = omp_get_wtime() - time;


		fwrite(&size, sizeof(size), 1, fRadixResult);
		fwrite(&time, sizeof(time), 1, fRadixResult);
		fwrite(array, sizeof(*array), size, fRadixResult);

		delete[]array;

		time = omp_get_wtime();
		ParallelSort(array2, size, num_threads);
		time = omp_get_wtime() - time;

		fwrite(&size, sizeof(size), 1, fParallelResult);
		fwrite(&time, sizeof(time), 1, fParallelResult);
		fwrite(array2, sizeof(*array2), size, fParallelResult);

		delete[] array2;

		fclose(fArray);
		fclose(fRadixResult);
		fclose(fParallelResult);
	}
	return 0;
}