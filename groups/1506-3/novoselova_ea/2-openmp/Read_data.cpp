#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <omp.h>
#include <random>
#include<iostream>
#include <fstream>
#include<conio.h>
#include<string>
#include<tbb/task_scheduler_init.h>
#include<tbb/tick_count.h>
int NewSize(int N)
{
	int result = N;
	if (floor(log2(N)) != log2(N))
	{
		int power = (int)log2(N) + 1;
		result = pow(2, power);
	}
	return result;
}
void Expansion(int *Matrix, int *newMatrix, int N, int newN)
{
	for (int i = 0; i < newN; i++)
	{
		for (int j = 0; j < newN; j++)
		{
			if (i >= N || j >= N)
				newMatrix[i * newN + j] = 0;
			else
				newMatrix[i * newN + j] = Matrix[i * N + j];
		}
	}
}

void Deformation(int *Matrix, int *newMatrix, int N, int newN)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Matrix[i * N + j] = newMatrix[i * newN + j];
		}
	}
}

int Strassen(int *MatrixA, int *MatrixB, int *MatrixC, int N);
int OMPStrassen(int *MatrixA, int *MatrixB, int *MatrixC, int N);

int main(int argc, char * argv[])
{
	int num_threads = 10;
	int countTest = 1;
	if (argc > 1)
	{
		num_threads = atoi(argv[1]);
	}
	if (argc > 2)
	{
		countTest = atoi(argv[2]);
	}
	int N;
	int *A;
	int *B;
	int *C;

	for (int i = 1; i <= countTest; i++)
	{
		char index[10];
		freopen(_itoa(i, index, 10), "rb", stdin);
		freopen(strcat(_itoa(i, index, 10), ".ans"), "wb", stdout);
		fread(&N, sizeof(N), 1, stdin);
		A = new int[N * N];
		B = new int[N * N];
		C = new int[N * N];

		fread(A, sizeof(*A), N * N, stdin);
		fread(B, sizeof(*B), N * N, stdin);

		omp_set_num_threads(num_threads);

		double timeSer, timePar;

		int newSize = NewSize(N);
		if (newSize == N)
		{
			timeSer = omp_get_wtime();
			Strassen(A, B, C, N);
			timeSer = omp_get_wtime() - timeSer;

			
			timePar = omp_get_wtime();
			OMPStrassen(A, B, C, N);
			timePar = omp_get_wtime() - timePar;

		}
		else
		{
			int *newA;
			int *newB;
			int *newC;
			newA = new int[newSize * newSize];
			newB = new int[newSize * newSize];
			newC = new int[newSize * newSize];

			Expansion(A, newA, N, newSize);
			Expansion(B, newB, N, newSize);
			Expansion(C, newC, N, newSize);

			timeSer = omp_get_wtime();
			Strassen(newA, newB, newC, newSize);
			timeSer = omp_get_wtime() - timeSer;

			timePar = omp_get_wtime();
			OMPStrassen(newA, newB, newC, newSize);
			timePar = omp_get_wtime() - timePar;

			Deformation(C, newC, N, newSize);

			delete[]newA;
			delete[]newB;
			delete[]newC;
		}
		fwrite(&timeSer, sizeof(timeSer), 1, stdout);
		fwrite(&timePar, sizeof(timePar), 1, stdout);
		fwrite(&N, sizeof(N), 1, stdout);
		fwrite(C, sizeof(*C), N * N, stdout);
		fclose(stdout);
		fclose(stdin);
		delete[]A;
		delete[]B;
		delete[]C;
	}
	return 0;
}
