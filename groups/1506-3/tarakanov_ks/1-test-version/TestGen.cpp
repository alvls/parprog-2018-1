#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

int n_tests[] = { 1, 4, 6, 8, 9, 100, 600, 700, 1000, 1500, 2000 };
int n_sizeBlocks[] = { 1, 2, 3, 2, 3, 20, 100, 350, 200, 2, 500 };

void MatrMulti(double* A[], double* B[], double* C[], int N);
void StringName_to_CharName(string str, char* ch);

int main(int argc, char * argv[])
{
	FILE* matr_in;
	FILE *perfect; // Эталон

	// Имена файлов
	char* fileName = "matr.in";
	char* answerName = "answer.ans";

	// Создаём генератор случайных чисел
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	// Cоздаём равномерное распределение случайной величины
	uniform_real_distribution<double> distribution(-100.00, 100.00);

	// Задаём размеры матриц и блока
	int n = 100;
	int sizeblock = 2;

	// Если передали номер теста в аргументах командной строки,
	//  то берём размер из n_tests, а размер блока из n_sizeBlocks
	if (argc > 1)
	{
		n = n_tests[atoi(argv[1])];
		sizeblock = n_sizeBlocks[atoi(argv[1])];

		// Формируем новое имя файла с матрицами
		fileName = argv[1]; 
		// Формируем новое имя файла для эталона
		string str = string(argv[1]) + string(".ans");
		answerName = new char[str.length()];
		StringName_to_CharName(str, answerName);
	}

	freopen_s(&matr_in, fileName, "wb", stdout);
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
	double dice_roll;
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


	freopen_s(&perfect, answerName, "wb", stdout);

	for (int i = 0; i < n; i++)
	{
		// записываем строку в бинарном виде в файл
		fwrite(C[i], sizeof(double), n, perfect);
	}

	fwrite(&time, sizeof(time), 1, perfect);

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

void StringName_to_CharName(string str, char* ch)
{
	for (int i = 0; i < str.length(); i++)
		ch[i] = str[i];
}
