#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <complex>
#include <iostream>
#include <stdlib.h>

using namespace std;

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



	fclose(fp);
	if (argc == 3)
	{
		err = fopen_s(&fp, argv[2], "w");
	}
	else
	{
		err = fopen_s(&fp, "output.txt", "w");
	}
	fprintf(fp, "%i \n", n);
	fprintf(fp, " %i \n", a);
	fprintf(fp, "%i \n", b);
	for (int i = 0; i < a*n; i++)
	{
		fprintf(fp, "%lf \n", a_value[i]);
	}
	for (int i = 0; i < b*n; i++)
	{
		fprintf(fp, "%lf \n", b_value[i]);
	}
	for (int i = 0; i < a*n; i++)
	{
		fprintf(fp, "%i \n", a_col[i]);
	}
	for (int i = 0; i < b*n; i++)
	{
		fprintf(fp, "%i \n", b_col[i]);
	}
	for (int i = 0; i < n+1; i++)
	{
		fprintf(fp, "%i \n", a_row[i]);
	}
	for (int i = 0; i < n+1; i++)
	{
		fprintf(fp, "%i \n", b_row[i]);
	}
	fclose(fp);
	delete(a_value);
	delete(b_value);
	delete(a_col);
	delete(b_col);
	delete(a_row);
	delete(b_row);
	return 0;
}