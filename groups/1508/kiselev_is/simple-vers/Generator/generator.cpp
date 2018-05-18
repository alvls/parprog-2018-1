#pragma once

#include <cstdio> 
#include <random> 
#include <ctime> 
#include <chrono>
using namespace std;

int n_tests[] = { 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };

int main(int argc, char * argv[]) {
	// перенаправляем поток stdout в файл matr.in 
	freopen("../tests/39", "wb", stdout);
	// создаём генератор случайных чисел с seed равным количеству времени с начала эпохи 
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	// создаём равномерное распределение случайной величины типа double в диапазоне // [-10, 10] 
	uniform_real_distribution <double> distribution(0, 15);				// Функция которую я использую для возведения числа в степень
	// задаём размер матриц												// Принимает только положительные значения
	int size = rand()% 12 + 1;
	// если передали номер теста в аргументах командной строки, то берём размер из 	n_tests 
	if (argc > 1) size = n_tests[atoi(argv[1])];
	// записываем в бинарном виде размерность матриц 
	fwrite(&size, sizeof(size), 1, stdout);
	// создаём временный массив для строки матрицы 
	double * cur = new double[size];
	// генерируем первую матрицу 
	for (int i = 0; i < 7; i++) {
		// заполняем случайными числами из равномерного распределения очередную строку матрицы 
		for (int j = 0; j < size; j++) cur[j] = distribution(generator);
		// записываем строку в бинарном виде в файл
		fwrite(cur, sizeof(*cur), size, stdout);
	}
	double confines[2];
	// задаем границы интегрирования
	confines[0] = distribution(generator);		// для X
	confines[1] = distribution(generator);
	if (confines[0] > confines[1]) swap(confines[0], confines[1]);
	fwrite(confines, sizeof(*confines), 2, stdout);

	confines[0] = distribution(generator);		// для Y
	confines[1] = distribution(generator);
	if (confines[0] > confines[1]) swap(confines[0], confines[1]);
	fwrite(confines, sizeof(*confines), 2, stdout);

	return 0;
}