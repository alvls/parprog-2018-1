// Генератор тестов
#include <cstdio>
#include <random>
#include <chrono>
#include <vector>
#include <string>

using namespace std;

// 25 вариантов размера теста
int n_tests[] = { /*№1*/1, /*№2*/2, /*№3*/2, /*№4*/5, /*№5*/5, /*№6*/10, /*№7*/10, /*№8*/100, /*№9*/100, /*№10*/500, /*№11*/1000, /*№12*/2000, /*№13*/5000,
/*№14*/10000, /*№15*/25000, /*№16*/50000, /*№17*/100000, /*№18*/200000, /*№19*/500000, /*№20*/1000000, /*№21*/2000000, /*№22*/5000000, /*№23*/10000000, /*№24*/50000000, /*№25*/100000000 };

int main(int argc, char * argv[])
{
	// создаём генератор случайных чисел с seed равным количеству времени с начала эпохи
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	// создаём равномерное распределение случайной величины типа int в диапазоне [-100000000, 100000000]
	uniform_int_distribution <int> distribution(-1e8, 1e8);
	// размер теста
	int n;

	if (argc <= 1)
		return 0;

	// перенаправляем поток stdout в файл
	freopen((".\\tests\\" + string(argv[1])).c_str(), "wb", stdout);
	// если передали номер теста в аргументах командной строки, то берём размер из n_tests 
	//(номера тестов для ввода начинаются с единицы)
	n = n_tests[atoi(argv[1]) - 1];
	//записываем количество элементов как фиктивное время для проверки Viewer'ом
	fwrite(&n, sizeof(double), 1, stdout);
	// записываем в бинарном виде количество элементов массива
	fwrite(&n, sizeof(int), 1, stdout);
	// создаём вектор для генерации чисел
	vector<int> vec(n);
	// генерируем
	for (size_t i = 0; i < n; ++i)
	{
		vec[i] = distribution(generator);
	}
	// записываем вектор в бинарном виде в файл
	fwrite(vec.data(), sizeof(int), n, stdout);

	fclose(stdout);
}
