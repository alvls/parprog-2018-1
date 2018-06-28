#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <complex>
#include <iostream>
#include <stdlib.h>
#include "sparse_matrix.h"
#include <time.h>

using namespace std;


////////////////////////MAIN///////////////////////////////////
int main(int argc, char* argv[])
{
	FILE* fp;
	errno_t err = 0;
	if (argc >= 2)
	{
		err = fopen_s(&fp, argv[1], "rb");
	}
	else
	{
		err = fopen_s(&fp, "input", "rb");
	}
	int n;
	fread_s(&n, sizeof(int), sizeof(int), 1, fp);
	int a;
	fread_s(&a, sizeof(int), sizeof(int), 1, fp);
	int b;
	fread_s(&b, sizeof(int), sizeof(int), 1, fp);
	complex<double> * a_value = new complex<double>[a*n];
	fread(a_value,  sizeof(complex<double>), a*n, fp);
	complex<double> * b_value = new complex<double>[b*n];
	fread(b_value, sizeof(complex<double>), b*n, fp);
	
	int * a_col = new int[a*n];
	fread(a_col,  sizeof(int),  a*n, fp);

	int * b_col = new int[b*n];
	fread(b_col,  sizeof(int),  b*n, fp);
	

	int * a_row = new int[n + 1];
	fread(a_row,  sizeof(int),  n+1, fp);

	int * b_row = new int[n+1];
	fread(b_row,  sizeof(int),  n+1, fp);

	sparse_matrix<std::complex<double>> A(n, n);
	A.SetValue(n, a_value, a_col, a_row);
	sparse_matrix<std::complex<double>> B(n, n);
	B.SetValue(n, b_value, b_col, b_row);
	sparse_matrix<std::complex<double>> * C = A.Matrix_Multyply(&B);

	fclose(fp);
	
	return 0;
}