#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <complex>
#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;



// Флаг - был ли инициализирован генератор случайных чисел
bool isSrandCalled = false;

///////////////////////////////////////РАНДОМИТСЯ
///ЭЛЕМЕНТ////////////////////////////////////////////////////
double next()
{
	return ((double)rand() / (double)RAND_MAX);
}


complex<double> next_cmp()
{
	double a, b;
	//a = rand() % 40 - 20;
	//b = rand() % 40 - 20;
	a = ((double)rand() / (double)RAND_MAX);
	b = ((double)rand() / (double)RAND_MAX);
	complex<double> z(a, b);
	return z;
}


void generate_complex_matrix(int seed, int N, int not_null_elements, complex<double> *_Value,int *_Col, int *_RowIndex) // sparse_matrix<std::complex<double>> *A)
{
	//sparse_matrix<std::complex<double>> A(N,N);
	int* RowIndex; // Массив индексов строк (размер N + 1)
	RowIndex = new int[N + 1];
	int i, j, k, f, tmp, notNull, c;	
	notNull = not_null_elements * N;
	complex<double>* Value; // Массив значений (размер NZ)
	Value = new complex<double>[notNull];
	int* Col; // Массив номеров столбцов (размер NZ)
	Col = new int[notNull];
	if (!isSrandCalled) {
		srand(seed);
		isSrandCalled = true;
	}
	//InitializeMatrix(N, notNull, mtx);
	for (i = 0; i < N; i++) {
		// Формируем номера столбцов в строке i
		for (j = 0; j < not_null_elements; j++) {
			do {
				Col[i * not_null_elements + j] = rand() % N;
				f = 0;
				for (k = 0; k < j; k++)
					if (Col[i * not_null_elements + j] == Col[i * not_null_elements + k])
						f = 1;
			} while (f == 1);
		}
		// Сортируем номера столцов в строке i
		for (j = 0; j < not_null_elements - 1; j++)
			for (k = 0; k < not_null_elements - 1; k++)
				if (Col[i * not_null_elements + k] > Col[i * not_null_elements + k + 1]) {
					tmp = Col[i * not_null_elements + k];
					Col[i * not_null_elements + k] = Col[i * not_null_elements + k + 1];
					Col[i * not_null_elements + k + 1] = tmp;
				}
	}
	// Заполняем массив значений
	for (i = 0; i < not_null_elements * N; i++)
		Value[i] = next_cmp();
	// Заполняем массив индексов строк
	c = 0;
	for (i = 0; i <= N; i++) {
		RowIndex[i] = c;
		c += not_null_elements;
	}
	for (i = 0; i < not_null_elements * N; i++)
	{
		_Value[i] = Value[i];
		_Col[i] = Col[i];
	}
	for (i = 0; i < N + 1; i++)
	{
		_RowIndex[i] =RowIndex[i];
	}
	//A->SetValue(notNull, Value, Col, RowIndex);
	/*A.Show();
	A.crs_to_standart();*/
}









int main(int argc, char * argv[])
{
	char *file_name;
	int N,NZ;
	int not_null;
	if (argc > 1)
	{
		N =atoi(argv[1]);
		NZ=atoi(argv[2]);
		file_name=argv[3];
	}
	if (argc > 1)
	{
		cout<<"test size "<<N<<endl;
		cout<<"test count "<<NZ<<endl;
		cout<<"test name "<<file_name<<endl;
	}
	else
	{
		cout<<"Enter size of matrix: ";
		cin>>N;
		cout<<"Enter count of not null elements in one col: ";
		cin>>NZ;
		cout<<"Enter file name: ";
		cin>>file_name;
	}
	FILE *fl=fopen(file_name,"wb");
	fwrite(&N,sizeof(N),1,fl);
	
	not_null = N * NZ;
	fwrite(&NZ,sizeof(NZ),1,fl);
	fwrite(&NZ,sizeof(NZ),1,fl);
	complex<double>* A_Value; 
	A_Value = new complex<double>[not_null];
	int* A_Col; 
	A_Col = new int[not_null];
	int* A_RowIndex; 
	A_RowIndex = new int[N + 1];
	complex<double>* B_Value; 
	B_Value = new complex<double>[not_null];
	int* B_Col; 
	B_Col = new int[not_null];
	int* B_RowIndex; 
	B_RowIndex = new int[N + 1];

	
	generate_complex_matrix(1, N, NZ,A_Value,A_Col,A_RowIndex); 
	generate_complex_matrix(1, N, NZ,B_Value,B_Col,B_RowIndex); 
	fwrite(A_Value,sizeof(*A_Value),not_null,fl);
	fwrite(B_Value,sizeof(*B_Value),not_null,fl);
	fwrite(A_Col,sizeof(*A_Col),not_null,fl);
	fwrite(B_Col,sizeof(*B_Col),not_null,fl);
	fwrite(A_RowIndex,sizeof(*A_RowIndex),N+1,fl);
	fwrite(B_RowIndex,sizeof(*B_RowIndex),N+1,fl);
	
	return 0;
}
	