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
	FILE *fp;
	fp = fopen(argv[1], "r");
	fscanf(fp, "%lf\n", &time);
	fscanf(fp, "%d\n", &count);
	values = new double[count];
	for (int i = 0; i < count; i++)
		fscanf(fp, "%lf\n", &values[i]);

	freopen(argv[2], "wb", stdin);

	fwrite(&time, sizeof(time), 1, stdin);
	fwrite(&count, sizeof(count), 1, stdin);
	fwrite(values, sizeof(*values), count, stdin);
	return 0;
}