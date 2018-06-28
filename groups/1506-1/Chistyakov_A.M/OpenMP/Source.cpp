#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "sparse_matrix.h"
#include "initialization_matrix.h"
#include <complex>
#include <iostream>
#include <ctime>
#include <stdlib.h>

int  main()
{
	/*using namespace std::complex_literals;
	
	sparse_matrix<std::complex<double>> A(4, 4);
	std::complex<double> A_val[6]{ { 4,5 },{ 3,-2 },{ 3,2 },{ 1,-1 },{ 5,4 },{ 3,-3 } };
	int A_kf[6]{ 1,3,2,0,2,3 };
	int A_ln[5]{ 0,2,3,3,6 };
	A.SetValue(6, A_val, A_kf, A_ln);
	sparse_matrix<std::complex<double>> B(4, 4);
	std::complex<double> B_val[4]{ { 1,1 },{ 1,3 },{ 4,4 },{ 2,-3 } };
	int B_kf[4]{ 0,1,2,3};
	int B_ln[5]{ 0,1,2,3,4 };
	B.SetValue(5, B_val, B_kf, B_ln);
	sparse_matrix<std::complex<double>> * C = A.Matrix_Multyply(&B);
	C->Show();*/


	/*complex<double> **s_values;
	s_values = new complex<double>*[4];
	for (int i = 0; i<4; i++)
	{
		s_values[i] = new complex<double>[4];
	}
	complex<double> **a_values;
	a_values = new complex<double>*[4];
	for (int i = 0; i<4; i++)
	{
		a_values[i] = new complex<double>[4];
	}
	complex<double> **product;
	product = new complex<double>*[4];
	for (int i = 0; i<4; i++)
	{
		product[i] = new complex<double>[4];
	}*/

	float start_time;
	float end_time;

	sparse_matrix<std::complex<double>> B(4000,4000);
	generate_complex_matrix(1, 4000, 400, &B);
	sparse_matrix<std::complex<double>> A(4000,4000);
	generate_complex_matrix(1, 4000, 400, &A);
	sparse_matrix<std::complex<double>>* C;
	start_time = clock();
	C=A.Matrix_Multyply(&B);
	end_time = clock();
	cout<< end_time - start_time<<endl;
	//C->Show();
	return 0;
}
	/*B.crs_to_standart(s_values);
	sparse_matrix<std::complex<double>> A(4, 4);
	generate_complex_matrix(1, 4, 2, &A);
	A.Show();
	A.crs_to_standart(a_values);
	
	cout << endl << "===========================" << endl;
	MultiplyWithOutAMP(s_values, a_values, product);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << product[i][j] << "  ";
		}
		cout << endl;
	}
	return 0;
}


////////////////////////MAIN///////////////////////////////////
//int main(int argc, char * argv[])
//{
//	char *file_name;
//	int N, NZ;
//	/////////////////
//	if (argc > 1)
//	{
//		N = atoi(argv[1]);
//		NZ = atoi(argv[2]);
//		file_name = argv[3];
//	}
//	/////////////////
//	if (argc > 1)
//	{
//		cout << "test size " << N << endl;
//		cout << "test count " << NZ << endl;
//		cout << "test name " << file_name << endl;
//	}
//	else
//	{
//		cout << "Enter size of matrix: ";
//		cin >> N;
//		cout << "Enter count of not null elements in one col: ";
//		cin >> NZ;
//		cout << "Enter file name: ";
//		cin >> file_name;
//	}
//
//
//	FILE *fl;
//	fl= fopen("test", "rb");
//	int test_size, test_count;
//	fread(&test_size,sizeof(test_size),1,fl);
//	cout<<"we have "<<test_size<<" size"<<endl;
//	fread(&test_count,sizeof(test_count),1,fl);
//	cout<<"we have "<<test_count<<" count"<<endl;
//	sparse_matrix<std::complex<double>> B(test_size, test_size);
//	complex<double> *tmp_values = new complex<double>[test_count*test_size];
//	fread(tmp_values, sizeof(sparse_matrix<std::complex<double>>), test_size*test_count, fl);
//	int *tmp_Col = new int[test_count];
//	int *tmp_RowIndex = new int[test_size + 1];
//	fread(tmp_Col,sizeof(tmp_Col),test_size*test_count,fl);
//	fread(tmp_RowIndex,sizeof(tmp_RowIndex),test_size+1,fl);
//	B.SetValue(test_count, tmp_values, tmp_Col, tmp_RowIndex);
//	sparse_matrix<std::complex<double>> A(test_size, test_size);/*
//	complex<double> *tmp_values = new complex<double>[test_count*test_size];*/
//	fread(tmp_values, sizeof(sparse_matrix<std::complex<double>>), test_size*test_count, fl);
//	/*int *tmp_Col = new int[test_count];
//	int *tmp_RowIndex = new int[test_size + 1];*/
//	fread(tmp_Col, sizeof(tmp_Col), test_size*test_count, fl);
//	fread(tmp_RowIndex, sizeof(tmp_RowIndex), test_size + 1, fl);
//	A.SetValue(test_count, tmp_values, tmp_Col, tmp_RowIndex);
//
//	fclose(fl);
//	return 0;
//}