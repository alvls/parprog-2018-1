#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
using namespace std;
int n_tests[] = { 1, 10, 50, 100,300, 500, 750, 1000, 1500, 2500, 5000, 7000,8500, 10000, 15000, 20000 , 25000 ,500000, 700000 ,1000000 };

int main(int argc, char * argv[])
{
	// перенаправляем поток stdout в файл matr. in
	FILE *output_file = fopen("../massiv.in", "wb");
	// создаём генератор случайных чисел с seed равным количеству времени с начала эпохи
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	// создаём равномерное распределение случайной величины типа double в диапазоне
	// [ -10000, 10000]
	uniform_real_distribution <double> distribution(-1e4, 1e4);
	// задаём размер массива по умолчанию
	int n = 1;
	// если передали номер теста в аргументах командной строки, то берём размер из n_tests
	if (argc > 1)
		n = n_tests[atoi(argv[1])];
	// записываем в бинарном виде размерность матриц
	fwrite(&n, sizeof(n), 1, output_file);
	// создаём временный массив для строки матрицы
	double * current = new double[n];
	// генерируем массив
	for (int i = 0; i < n; i++)
	{
		// заполняем случайными числами массив из равномерного распределения
		current[i] = distribution(generator);
	}
	// записываем строку в бинарном виде в файл
	fwrite(current, sizeof(*current), n, output_file);

	fclose(output_file);
	return 0;
}
