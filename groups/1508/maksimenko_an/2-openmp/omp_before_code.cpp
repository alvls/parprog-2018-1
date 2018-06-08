#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <conio.h>
#include <fstream>
#include <iostream>
#include "omp_merge_sort.h"
#include <ctime>

int main(int argc, char * argv[])
{
	if (argc != 4) return 0;
	int count;
	double* values;
	int threads = 1;
	threads = atoi(argv[3]);
	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wb", stdout);

	fread(&count, sizeof(count), 1, stdin);

	values = new double[count];
	fread(values, sizeof(*values), count, stdin);
	vector<double> vector_values(count);

	for (int i = 0; i < count; i++) {
		vector_values[i] = values[i];
	}
	omp_set_num_threads(threads);
	double time = omp_get_wtime();
	vector_values = mergesort(vector_values, threads);
	time = omp_get_wtime() - time;

	for (int i = 0; i < count; i++)
		values[i] = vector_values[i];

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&count, sizeof(count), 1, stdout);
	fwrite(values, sizeof(*values), count, stdout);
	return 0;
}