//#include "Sol.cpp"
#include <iostream>
#include <cstdio>
#include <omp.h>
using namespace std;
//1-ln,	2-cos,	3-sin	,4-exp,	5-x^2,	6-x^3,	7-x^4,	8-x^5,	9-x^6,	10-x^1/2,	11-x^1/3,	12-x^1/4

double solver(double* a, double *b, int* f, int* z, int n, int kol);
double func(double* x, int *c, int *z, int k);
FILE *stream;

int main()
{
	int n = 3;
	char er = 'e';

	freopen_s(&stream, "20", "rb", stdin);
	fread(&n, sizeof(n), 1, stdin);

	double *a = new double[n];
	double *b = new double[n];
	int *c = new int[n];
	int *z = new int[n];
	
	fread(c, sizeof(*c), n, stdin);
	fread(z, sizeof(*z), n, stdin);
	fread(a, sizeof(*a), n, stdin);
	fread(b, sizeof(*b), n, stdin);
	fclose(stream);

	double time_ser = omp_get_wtime();
	double res_ser = solver(a, b, c, z, 50, n);
	time_ser = omp_get_wtime() - time_ser;

	freopen_s(&stream, "20.ans", "wb", stdout);
	fwrite(&time_ser, sizeof(time_ser), 1, stdout);
	fwrite(&res_ser, sizeof(res_ser), 1, stdout);
	if (res_ser == 1000000)
	{
		fwrite(&er, sizeof(char), 1, stdout);
	}
	fclose(stream);
	delete[]a;
	delete[]b;
	delete[]c;
	delete[]z;
	return 0;
}