#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include <iostream>

using namespace std;
// каждому номеру теста соответствует колличество элементов в массиве
int n_tests[] = { 1, 2, 3, 5, 7, 8, 9, 10, 10, 1000, 10000, 10000, 10000, 500000, 100000, 1000000, 10000000, 25000000, 50000000, 100000000 };

int main(int argc, char * argv[]) {
	// на вход должно подаваться одно число в диапозоне от [0,20] с целью уникальности теста
	if (argc != 2 || atoi(argv[1]) < 1 || atoi(argv[1]) > 20) return 0;
	// определяем размерность нашего массива
	int n = n_tests[atoi(argv[1]) - 1];
	// создаём файл(или перезаписываем если он существует) в который будем записывать результат работы программы
	freopen(argv[1], "wb", stdout);
	// создаём генератор случайных чисел с seed равным количеству времени с начала эпохи
	default_random_engine generator(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
	// создаём равномерное распределение случайной величины типа double в диапазоне [-10000, 10000] 
	uniform_real_distribution <double> distribution(-1e4, 1e4);
	// записываем кол-во элементов массива
	fwrite(&n, sizeof(n), 1, stdout);

	double *values = new double[n];
	// заполнение массива одинаковыми элементами
	if (n == 12) {
		double value = distribution(generator);
		for (int i = 0; i < n; i++)
			values[i] = value;
	}
	else
		// заполнение массива по невозрастанию
		if (n == 13) {
			double value = distribution(generator);
			for (int i = 0; i < n; i++)
				values[i] = value - i;
		}
		else
			// заполнение массива не по убыванию
			if (n == 14) {
				double value = distribution(generator);
				for (int i = 0; i < n; i++)
					values[i] = value + i;
			}
			else
				// заполнение массива случайными элементами типа double в диапозоне от [-10000, 10000] 
				for (int i = 0; i < n; i++) {
					values[i] = distribution(generator);
				}
	// запись массива в файл
	fwrite(values, sizeof(*values), n, stdout);
	return 0;
}