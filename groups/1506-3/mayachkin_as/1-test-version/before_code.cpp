
#include <cstdio>
#include <fstream>
#include <random>
#include <omp.h>
#include <string>

using namespace std;

void RadixSort(double* data, int dataLength);

int main(int argc, char * argv[])
{
	/*int num_threads = 1;
	if (argc > 1)
		num_threads = atoi(argv[1]);*/
	int sizeArray;
	double* array;

	freopen("1", "rb", stdin);
	freopen("1.ans", "wb", stdout);

	fread(&sizeArray, sizeof(sizeArray), 1, stdin);

	array = new double[sizeArray];

	fread(array, sizeof(*array), sizeArray, stdin);

	//omp_set_num_threads(num_threads);

	double time = omp_get_wtime();
	RadixSort(array, sizeArray);
	time = omp_get_wtime() - time;

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(array, sizeof(*array), sizeArray, stdout);

	delete[] array;
	return 0;
}