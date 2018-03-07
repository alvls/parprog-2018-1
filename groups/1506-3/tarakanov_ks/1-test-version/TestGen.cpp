#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include <iostream>
#include <Windows.h>

using namespace std;

int n_tests[] = { 1, 4, 6, 8, 9, 100, 600, 700, 1000, 1500, 2000 };
int n_sizeBlocks[] = { 1, 2, 3, 2, 3, 20, 100, 350, 200, 2, 500 };

void MatrMulti(double* A[], double* B[], double* C[], int N);

int main(int argc, char * argv[])
{
	//cout << argc << endl;
	/*if (argc > 1)
	{
		cout << argv[1] << endl;
	}*/
	FILE* matr_in, *perfect;


	// Создаём генератор случайных чисел
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	// Cоздаём равномерное распределение случайной величины
	uniform_int_distribution<int> distribution(1, 9);

	// Задаём размеры матриц и блока
	int n = 8;
	int sizeblock = 2;



	// Если передали номер теста в аргументах командной строки,
	//  то берём размер из n_tests, а размер блока из n_sizeBlocks
	if (argc > 1)
	{
		n = n_tests[atoi(argv[1])];
		sizeblock = n_sizeBlocks[atoi(argv[1])];
	}
	cout << "here" << endl;
	cout << n << " " << sizeblock << endl;
	freopen_s(&matr_in, "matr.in", "wb", stdout);
	// Записываем в бинарном виде размерность матриц
	fwrite(&n, sizeof(n), 1, stdout);
	// Записываем в бинарном виде размер блока
	fwrite(&sizeblock, sizeof(sizeblock), 1, stdout);

	// Матрицы для формирования эталона
	double **A = new double*[n];
	for (int count = 0; count < n; count++)
		A[count] = new double[n];

	double **B = new double*[n];
	for (int count = 0; count < n; count++)
		B[count] = new double[n];

	double **C = new double*[n];
	for (int count = 0; count < n; count++)
		C[count] = new double[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			C[i][j] = 0;
		}

	// Создаём временный массив для строки матрицы
	double * cur = new double[n];
	int dice_roll;
	// Генерируем первую матрицу
	for (int i = 0; i < n; i++)
	{
		// Заполнение строки матрицы случайными числами
		for (int j = 0; j < n; j++)
		{
			dice_roll = distribution(generator);
			cur[j] = dice_roll;
			A[i][j] = dice_roll;
		}
		// Записываем строку в бинарном виде в файл
		fwrite(cur, sizeof(*cur), n, stdout);
	}
	// Аналогично генерируем вторую матрицу
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			dice_roll = distribution(generator);
			cur[j] = dice_roll;
			B[i][j] = dice_roll;
		}
		fwrite(cur, sizeof(*cur), n, stdout);
	}

	fclose(matr_in);



	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	// Формирование эталона
	MatrMulti(A, B, C, n);

	end = std::chrono::system_clock::now();

	double time = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

	//fopen_s(&perfect, "answer.out", "wb");
	freopen_s(&perfect, "answer.out", "wb", stdout);
	fwrite(&time, sizeof(time), 1, perfect);
	//freopen_s(&perfect, "answer.out", "wb", stdout);

	for (int i = 0; i < n; i++)
	{
		// записываем строку в бинарном виде в файл
		fwrite(C[i], sizeof(double), n, perfect);
	}

	fclose(perfect);

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