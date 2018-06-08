#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <conio.h>
#include <fstream>
#include <iostream>
using namespace std;
int main(int argc, char * argv[]) {
	int count;
	double* values;
	double time;
	freopen(argv[1], "rb", stdin);

	fread(&time, sizeof(time), 1, stdin);
	fread(&count, sizeof(count), 1, stdin);
	values = new double[count];
	fread(values, sizeof(*values), count, stdin);

	FILE *fp;
	fp = fopen(argv[2], "w");
	fprintf(fp, "%lf\n", time);
	fprintf(fp, "%d\n", count);
	for (int i = 0; i < count; i++)
		fprintf(fp, "%lf\n", values[i]);
	return 0;
}