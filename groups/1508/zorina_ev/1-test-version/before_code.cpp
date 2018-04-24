#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <omp.h>
#include <ctime>
#include <iostream>


void HoaraQuickSort(int* arr, int first, int last);
void QuickSort(int* arr, int size);

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		std::cout << "Enter [input.bin] [output.bin] " << std::endl;
		return 1;
	}

	int size;
	int *arr;
	double time;

	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wb", stdout);
	fread(&time, sizeof(double), 1, stdin);
	fread(&size, sizeof(int), 1, stdin);

	arr = new int[size];

	fread(arr, sizeof(*arr), size, stdin);

	time = omp_get_wtime();
	HoaraQuickSort(arr, 0, size - 1);
	time = omp_get_wtime() - time;

	fwrite(&time, sizeof(double), 1, stdout);
	fwrite(&size, sizeof(int), 1, stdout);
	fwrite(arr, sizeof(*arr), size, stdout);

	return 0;
}
