#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "sparse_matrix.h"
#include "initialization_matrix.h"
#include <complex>
#include <iostream>
#include <stdlib.h>


class MPL
{
public:
	MPL()
	{};


	void operator( )(const tbb::blocked_range<int>& r) const
	{
		int begin = r.begin(), end = r.end();

		int size = end - begin;

	}
};



//////////////////////MAIN///////////////////////////////////
int main(int argc, char * argv[])
{
	char *file_name;
	int N, NZ;
	/////////////////
	if (argc > 1)
	{
		N = atoi(argv[1]);
		NZ = atoi(argv[2]);
		file_name = argv[3];
	}
	/////////////////
	if (argc > 1)
	{
		cout << "test size " << N << endl;
		cout << "test count " << NZ << endl;
		cout << "test name " << file_name << endl;
	}
	else
	{
		cout << "Enter size of matrix: ";
		cin >> N;
		cout << "Enter count of not null elements in one col: ";
		cin >> NZ;
		cout << "Enter file name: ";
		cin >> file_name;
	}


	FILE *fl;
	fl= fopen("test", "rb");
	int test_size, test_count;
	fread(&test_size,sizeof(test_size),1,fl);
	cout<<"we have "<<test_size<<" size"<<endl;
	fread(&test_count,sizeof(test_count),1,fl);
	cout<<"we have "<<test_count<<" count"<<endl;
	sparse_matrix<std::complex<double>> B(test_size, test_size);
	complex<double> *tmp_values = new complex<double>[test_count*test_size];
	fread(tmp_values, sizeof(sparse_matrix<std::complex<double>>), test_size*test_count, fl);
	int *tmp_Col = new int[test_count];
	int *tmp_RowIndex = new int[test_size + 1];
	fread(tmp_Col,sizeof(tmp_Col),test_size*test_count,fl);
	fread(tmp_RowIndex,sizeof(tmp_RowIndex),test_size+1,fl);
	B.SetValue(test_count, tmp_values, tmp_Col, tmp_RowIndex);
	sparse_matrix<std::complex<double>> A(test_size, test_size);/*
	complex<double> *tmp_values = new complex<double>[test_count*test_size];*/
	fread(tmp_values, sizeof(sparse_matrix<std::complex<double>>), test_size*test_count, fl);
	/*int *tmp_Col = new int[test_count];
	int *tmp_RowIndex = new int[test_size + 1];*/
	fread(tmp_Col, sizeof(tmp_Col), test_size*test_count, fl);
	fread(tmp_RowIndex, sizeof(tmp_RowIndex), test_size + 1, fl);
	A.SetValue(test_count, tmp_values, tmp_Col, tmp_RowIndex);

	fclose(fl);
	return 0;
}