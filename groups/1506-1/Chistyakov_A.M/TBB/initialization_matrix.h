#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <complex>
#include "sparse_matrix.h"

#include "tbb\task_scheduler_init.h"
#include "tbb\parallel_for.h"
#include "tbb\blocked_range.h"



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


void generate_complex_matrix(int seed, int N, int not_null_elements, sparse_matrix<std::complex<double>> *A)
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
	A->SetValue(notNull, Value, Col, RowIndex);
	/*A.Show();
	A.crs_to_standart();*/
}



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
