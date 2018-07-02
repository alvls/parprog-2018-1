#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <complex>
#include <iostream>
#include <stdlib.h>
#include "sparse_matrix.h"

using namespace std;

void MultiplyWithOutAMP(complex<double> **aMatrix, complex<double> **bMatrix, complex<double> **product)
{

	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			// Multiply the row of A by the column of B to get the row, column of product.  
			for (int inner = 0; inner < 4; inner++) {
				product[row][col] += aMatrix[row][inner] * bMatrix[inner][col];
			}
			
		}
		
	}
}


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

	complex<double> **A_values;
	A_values = new complex<double>*[n];
	for (int i = 0; i<n; i++)
	{
		A_values[i] = new complex<double>[n];
	}
	complex<double> **B_values;
	B_values = new complex<double>*[n];
	for (int i = 0; i<n; i++)
	{
		B_values[i] = new complex<double>[n];
	}
	complex<double> **C_values;
	C_values = new complex<double>*[n];
	for (int i = 0; i<n; i++)
	{
		C_values[i] = new complex<double>[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; i++)
		{
			A_values[i][j] = (0,0);
			B_values[i][j] = (0,0);
			C_values[i][j] = (0,0);
		}
	}
	sparse_matrix<std::complex<double>> A(n, n);
	A.SetValue(n, a_value, a_col, a_row);
	sparse_matrix<std::complex<double>> B(n, n);
	B.SetValue(n, b_value, b_col, b_row);
	A.crs_to_standart(A_values);
	B.crs_to_standart(B_values);
	MultiplyWithOutAMP(A_values,B_values,C_values);
	fclose(fp);
	FILE* fl;
	fopen_s(&fl, "output", "rb");
	int n1;
	fread_s(&n1, sizeof(int), sizeof(int), 1, fl);
	int r1;
	fread_s(&r1, sizeof(int), sizeof(int), 1, fl);
	complex<double> * r_value = new complex<double>[r1*n1];
	fread(r_value,  sizeof(complex<double>), r1*n1, fl);
	int * r_col = new int[r1*n];
	fread(r_col,  sizeof(int),  r1*n1, fl);

	int * r_row = new int[n1 + 1];
	fread(a_row,  sizeof(int),  n1+1, fp);
	sparse_matrix<std::complex<double>> R(n, n);
	complex<double> **R_values;
	R_values = new complex<double>*[n];
	R.SetValue(n1, r_value, r_col, r_row);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; i++)
		{
			R_values[i][j] = (0,0);
			
		}
	}
	int key = 1;
	R.crs_to_standart(R_values);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; i++)
		{
			if(R_values[i][j] != C_values[i][j] )
			{
				key = -1;
				break;
			}
			
		}
	}
	if (key = -1)
	{
		cout << "err";
	}
	else
	{
		cout << "true";
	}
	return 0;
}