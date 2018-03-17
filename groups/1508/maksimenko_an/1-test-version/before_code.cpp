#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <conio.h>
#include <fstream>
#include <iostream>
#include "sol.h"
#include <ctime>

int main(int argc, char * argv[])
{
	if (argc != 3) return 0;
	int count;
	double* values;

	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wb", stdout);

	fread(&count, sizeof(count), 1, stdin);

	values = new double[count];
	fread(values, sizeof(*values), 1, stdin);

	double time = clock();
	MergeSorting(0, count - 1, values, count);
	time = clock() - time;

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&count, sizeof(count), 1, stdout);
	fwrite(values, sizeof(*values), count, stdout);

	return 0;
}