#include <math.h>
#include <omp.h> 
#include <iostream>
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include <random>
#include <chrono>

using namespace tbb;
using namespace std;

class MoveBlock_A
{
private:
	double** const A; // Указатель на мтрицу A
	int _Nb; // Количество блоков матрицы
	int sizeblock; // Размер блока
	bool oneMove;
public:
	// К-р
	MoveBlock_A(double** const matrix, int nb, int _sizeblock, bool _oneMove) 
		: A(matrix), _Nb(nb), sizeblock(_sizeblock), oneMove(_oneMove) {};

	void operator() (const tbb::blocked_range<int> &range) const
	{
		int begin = range.begin(), end = range.end();

		for (int block = begin; block != end; block++)
		{
			if (oneMove)
				MoveBlock(A, block, _Nb, sizeblock);
			else
				for (int index = 0; index < block; index++)
					MoveBlock(A, block, _Nb, sizeblock);
		}
	}

	void MoveBlock(double** const A, const int lineNumber, const int _Nb, const int _jump) const 
	{
		int i, j, k;
		// _jump  На сколько двигаем элемент блока(сдвиг на размер блока)

		double **tmp = new double*[_jump];
		for (int count = 0; count < _jump; count++)
			tmp[count] = new double[_jump];

		// Запоминаем первый перемещаемый блок в строке
		for (i = 0; i<_jump; i++)
			for (j = 0; j<_jump; j++)
				tmp[i][j] = A[i + _jump * lineNumber][j];

		for (k = 0; k<_Nb - 1; k++)
		{
			for (i = 0; i<_jump; i++)
				for (j = 0; j<_jump; j++)
					A[i + _jump * lineNumber][j + _jump * k] = A[i + _jump * lineNumber][j + _jump * (k + 1)];
		}

		// Записываем 1 блок в конец
		for (i = 0; i<_jump; i++)
			for (j = 0; j < _jump; j++)
			{
				A[i + _jump * lineNumber][j + _jump * (_Nb - 1)] = tmp[i][j];
			}
	}
};

class MoveBlock_B
{
private:
	double** const B; // Указатель на мтрицу  B
	int _Nb; // Количество блоков матрицы
	int sizeblock; // Размер блока
	bool oneMove;
public:
	// К-р
	MoveBlock_B(double** const matrix, int nb, int _sizeblock, bool _oneMove) 
		: B(matrix), _Nb(nb), sizeblock(_sizeblock), oneMove(_oneMove) {};

	void operator() (const tbb::blocked_range<int> &range) const
	{
		int begin = range.begin(), end = range.end();

		for (int block = begin; block != end; block++)
		{
			if (oneMove)
				MoveBlock(B, block, _Nb, sizeblock);
			else
				for (int index = 0; index < block; index++)
					MoveBlock(B, block, _Nb, sizeblock);
		}
	}

	void MoveBlock(double** const B, const int lineNumber, const int _Nb, const int _jump) const
	{
		int i, j, k;
		// _jump  На сколько двигаем элемент блока(сдвиг на размер блока)

		double **tmp = new double*[_jump];
		for (int count = 0; count < _jump; count++)
			tmp[count] = new double[_jump];

		// Запоминаем первый перемещаемый блок в столбце
		for (i = 0; i<_jump; i++)
			for (j = 0; j<_jump; j++)
				tmp[i][j] = B[i][j + _jump * lineNumber];

		for (k = 0; k<_Nb - 1; k++)
		{
			for (i = 0; i<_jump; i++)
				for (j = 0; j<_jump; j++)
					B[i + _jump * k][j + _jump * lineNumber] = B[i + _jump * (k + 1)][j + _jump * lineNumber];
		}

		for (i = 0; i<_jump; i++)
			for (j = 0; j<_jump; j++)
				B[i + _jump * (_Nb - 1)][j + _jump * lineNumber] = tmp[i][j];
	}

};

class MultiBlock
{
private:
	double** const A; // Указатель на мтрицу A
	double** const B;
	double** const C;
	int _Nb; // Количество блоков матрицы
	int sizeblock; // Размер блока
public:
	// К-р
	MultiBlock(double** const matrixA, double** const matrixB, double** const matrixC, int nb, int _sizeblock)
		: A(matrixA), B(matrixB), C(matrixC), _Nb(nb), sizeblock(_sizeblock) {};

	void operator() (const tbb::blocked_range<int> &range) const
	{
		int begin = range.begin(), end = range.end();

		for (int block = begin; block != end; block++)
		{
			for (int j = 0; j < _Nb; j++)
				MutiplyBlock(A, B, C, block, j, sizeblock);
		}
	}

	void MutiplyBlock(double** const A, double** const B, double** const C, const int bi, const int bj, const int _jump) const
	{
		int i, j; // _jump размер умножаемых блоков;
		for (i = 0; i < _jump; i++)
			for (j = 0; j < _jump; j++)
				for (int k = 0; k < _jump; k++)
					C[i + _jump * bi][j + _jump * bj] += A[i + _jump * bi][_jump*bj + k] * B[k + _jump * bi][j + _jump * bj];
	}

};

void MatrMatrMult(double* A[], double* B[], double* C[], int N, int sizeBlock, int number_of_threads)
{
	int Nb; // Резмер сетки процессоров или количество блоков в матрице

	if (N % sizeBlock != 0)
	{
		// Не выполняется необходимое условие для выполнения алгоритма
		// Количетсво исполняющих процессоров должно быть полным квадратом

		// Запускаем обычный алгоритм умножения матриц
		int i, j, k;
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

		task_scheduler_init init(number_of_threads);
		parallel_for(blocked_range<int>(1, Nb, 1), MoveBlock_A(A, Nb, sizeBlock, false));
		init.terminate();

		init.initialize(number_of_threads);
		parallel_for(blocked_range<int>(1, Nb, 1), MoveBlock_B(B, Nb, sizeBlock, false));
		init.terminate();

		// Выполняем стольок раз, какой размер у сетки процессоров
		for (int k = 0; k < Nb; k++)
		{
				init.initialize(number_of_threads);
				parallel_for(blocked_range<int>(0, Nb, 1), MultiBlock(A, B, C, Nb, sizeBlock));
				init.terminate();

				task_scheduler_init init(number_of_threads);
				parallel_for(blocked_range<int>(0, Nb, 1), MoveBlock_A(A, Nb, sizeBlock, true));
				init.terminate();

				init.initialize(number_of_threads);
				parallel_for(blocked_range<int>(0, Nb, 1), MoveBlock_B(B, Nb, sizeBlock, true));
				init.terminate();

		}
	}
}