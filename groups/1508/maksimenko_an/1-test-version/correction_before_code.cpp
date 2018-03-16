#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <conio.h>
#include <fstream>
#include <iostream>
#include "sol.h"
#include <ctime>

int main(int argc, char * argv[])
{
	int count = 0;
	double* values;
	FILE *fp;
	fp = fopen(argv[1],"r");
	fscanf(fp, "%d\n", &count);

	values = new double[count];
	for (int i = 0; i < count; i++)
		fscanf(fp, "%lf\n", &values[i]);
	fclose(fp);

	MergeSorting(0, count - 1, values, count);

	fp = fopen(argv[2], "w");
	fprintf(fp, "%d\n", count);
	for (int i = 0; i < count; i++)
		fprintf(fp, "%lf\n", values[i]);
	return 0;
}