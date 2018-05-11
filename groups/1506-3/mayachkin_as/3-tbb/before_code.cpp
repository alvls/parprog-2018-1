#define  _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <fstream>
#include <random>
#include <omp.h>
#include <string>

using namespace std;

void RadixSort(double* data, int dataLength);
void ParallelSort(double* data, int size, int pnum);
void TBBParallelSort(double *input, int size, int nThreads);

int tmain(int argc, char * argv[])
{
	int num_threads = 8;
	if (argc > 1)
		num_threads = atoi(argv[1]);
	int sizeArray;
	double* array;
	double* array2;

	int i = 24;
	string nameFile = to_string((long long)i);
	FILE* fArray = fopen(("./tests/" + nameFile).c_str(), "rb");
	FILE* fAnsRes = fopen(("./tests/" + nameFile + ".ans").c_str(), "wb");
	FILE* fParRes = fopen(("./tests/" + nameFile + ".testres").c_str(), "wb");

	fread(&sizeArray, sizeof(sizeArray), 1, fArray);

	array = new double[sizeArray];
	array2 = new double[sizeArray];

	fread(array, sizeof(*array), sizeArray, fArray);

	for (int j = 0; j < sizeArray; j++)
		array2[j] = array[j];

	double time = omp_get_wtime();
	RadixSort(array, sizeArray);
	time = omp_get_wtime() - time;

	fwrite(&sizeArray, sizeof(sizeArray), 1, fAnsRes);
	fwrite(&time, sizeof(time), 1, fAnsRes);
	fwrite(array, sizeof(*array), sizeArray, fAnsRes);

	time = omp_get_wtime();
	TBBParallelSort(array2, sizeArray, num_threads);
	time = omp_get_wtime() - time;

	fwrite(&sizeArray, sizeof(sizeArray), 1, fParRes);
	fwrite(&time, sizeof(time), 1, fParRes);
	fwrite(array2, sizeof(*array2), sizeArray, fParRes);

	fclose(fArray);
	fclose(fAnsRes);
	fclose(fParRes);

	delete[] array;
	return 0;
}