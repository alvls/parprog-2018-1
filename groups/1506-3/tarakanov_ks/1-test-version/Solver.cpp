#include <cstdio>
#include <random>
#include <iostream>
#include <windows.h>
#include <chrono>
#include <random>

void MatrMulti(double* A[], double* B[], double* C[], int N);

int main(int argc, char * argv[])
{
	int N, sizeBlock;

	FILE *matr_in, *matr_out;
	FILE* perfect;

	freopen_s(&matr_in, "matr.in", "rb", stdin);

	// Считываем размеры матриц
	fread(&N, sizeof(N), 1, stdin);
	fread(&sizeBlock, sizeof(sizeBlock), 1, stdin);

	// Выделение памяти для матриц
	double **A = new double*[N];
	for (int count = 0; count < N; count++)
		A[count] = new double[N];

	double **B = new double*[N];
	for (int count = 0; count < N; count++)
		B[count] = new double[N];

	double **C = new double*[N];
	for (int count = 0; count < N; count++)
		C[count] = new double[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			C[i][j] = 0;
		}

	// Считывание матриц A и B
	for (int i = 0; i < N; i++)
	{
		fread(A[i], sizeof(double), N, stdin);
	}
	for (int i = 0; i < N; i++)
	{
		fread(B[i], sizeof(double), N, stdin);
	}

	fclose(matr_in);

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	// Последовательное умножение матриц
	MatrMulti(A, B, C, N);

	std::cout << std::endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			std::cout << C[i][j] << " ";
		std::cout << std::endl;
	}

	end = std::chrono::system_clock::now();

	double time = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

	freopen_s(&matr_out, "matr.out", "wb", stdout);
	fwrite(&time, sizeof(time), 1, stdout);
	// Запись матрцы результата
	for (int i = 0; i < N; i++)
	{
		// записываем строку в бинарном виде в файл
		fwrite(C[i], sizeof(double), N, stdout);
	}

	fclose(matr_out);

	return 0;
}

void MatrMulti(double* A[], double* B[], double* C[], int N)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
}