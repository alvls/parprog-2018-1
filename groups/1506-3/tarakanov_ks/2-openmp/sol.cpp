#include <omp.h>
#include <math.h>
#include <iostream>

using namespace std;

void MoveBlock_A(double* A[], int lineNumber, int _Nb, int _jump)
{
	int i, j, k;
	// _jump  На сколько двигаем элемент блока(сдвиг на размер блока)

	double **tmp = new double*[_jump];
	for (int count = 0; count < _jump; count++)
		tmp[count] = new double[_jump];

	// Запоминаем первый перемещаемый блок в строке
	for (i = 0; i<_jump; i++)
		for (j = 0; j<_jump; j++)
			tmp[i][j] = A[i + _jump*lineNumber][j];

	for (k = 0; k<_Nb - 1; k++)
	{
		for (i = 0; i<_jump; i++)
			for (j = 0; j<_jump; j++)
				A[i + _jump*lineNumber][j + _jump*k] = A[i + _jump*lineNumber][j + _jump*(k + 1)];
	}

	// Записываем 1 блок в конец
	for (i = 0; i<_jump; i++)
		for (j = 0; j < _jump; j++)
		{
			A[i + _jump*lineNumber][j + _jump * (_Nb - 1)] = tmp[i][j];
		}
}

void MoveBlock_B(double* B[], int lineNumber, int _Nb, int _jump)
{
	int i, j, k;
	// _jump  На сколько двигаем элемент блока(сдвиг на размер блока)

	double **tmp = new double*[_jump];
	for (int count = 0; count < _jump; count++)
		tmp[count] = new double[_jump];

	// Запоминаем первый перемещаемый блок в столбце
	for (i = 0; i<_jump; i++)
		for (j = 0; j<_jump; j++)
			tmp[i][j] = B[i][j + _jump*lineNumber];

	for (k = 0; k<_Nb - 1; k++)
	{
		for (i = 0; i<_jump; i++)
			for (j = 0; j<_jump; j++)
				B[i + _jump*k][j + _jump*lineNumber] = B[i + _jump*(k + 1)][j + _jump*lineNumber];
	}

	for (i = 0; i<_jump; i++)
		for (j = 0; j<_jump; j++)
			B[i + _jump * (_Nb - 1)][j + _jump*lineNumber] = tmp[i][j];
}

void MutiplyBlock(double* A[], double* B[], double* C[], int bi, int bj, int _jump)
{
	int i, j; // _jump размер умножаемых блоков;
	for (i = 0; i < _jump; i++)
		for (j = 0; j < _jump; j++)
			for (int k = 0; k < _jump; k++)
				C[i + _jump*bi][j + _jump*bj] += A[i + _jump*bi][_jump*bj + k] * B[k + _jump*bi][j + _jump*bj];
}

void MatrMatrMult(double* A[], double* B[], double* C[], int N, int sizeBlock)
{
	int Nb; // Резмер сетки процессоров или количество блоков в матрице

	int i, j, k;
	
	if (N % sizeBlock != 0)
	{
		// Не выполняется необходимое условие для выполнения алгоритма
		// Количетсво исполняющих процессоров должно быть полным квадратом

		// Запускаем обычный алгоритм умножения матриц
		#pragma omp parallel shared(A,B,C) private(i,j,k)
		{
			//cout << omp_get_num_threads() << endl;
			#pragma omp for
			for (i = 0; i < N; i++)
			{
				for (k = 0; k < N; k++)
					for (j = 0; j < N; j++)
						C[i][j] += (A[i][k] * B[k][j]);
			}
		}

	}
	else
	{
		Nb = N / sizeBlock;

		#pragma omp parallel shared(A,B) private(i)   
		{
			// Каждый поток двигает свою строку блоков матрицы А
			#pragma omp for
			for (i = 1; i < Nb; i++)
			{
				// Цикл сколько раз нам нужно подвинуть блоки в строке
				for (int index = 0; index < i; index++)
					MoveBlock_A(A, i, Nb, sizeBlock);
			}
			// Двигаем столбцы матрицы B
			#pragma omp for
			for (i = 1; i < Nb; i++)
			{
				for (int index = 0; index < i; index++)
					MoveBlock_B(B, i, Nb, sizeBlock);
			}
		}

		// Выполняем стольок раз, какой размер у сетки процессоров
		for (k = 0; k < Nb; k++)
		{
			#pragma omp parallel shared( A, B, C ) private( i,j )   
			{

				#pragma omp for
				for (i = 0; i < Nb; i++)
				{
					for (j = 0; j < Nb; j++)
						MutiplyBlock(A, B, C, i, j, sizeBlock);
				}

				#pragma omp for
				for (i = 0; i < Nb; i++)
				{
					MoveBlock_A(A, i, Nb, sizeBlock);
				}

				#pragma omp for
				for (i = 0; i < Nb; i++)
				{
					MoveBlock_B(B, i, Nb, sizeBlock);
				}
			}
		}
	}
}