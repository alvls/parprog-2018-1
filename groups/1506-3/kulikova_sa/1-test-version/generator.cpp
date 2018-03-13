#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <random> 
#include <chrono>

int n_tests[] = { 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };

//argv[1] - размер системы, argv[2] - имя выходного файла
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");//Корректное отображение Кириллицы

	if (argc != 3) {
		std::cout << "Некорректные данные" << std::endl;
		return 1;
	}

	if (atoi(argv[1]) < 0 || atoi(argv[1]) > 24) {
		std::cout << "Некорректный номер теста" << std::endl;
		return 2;
	}

	FILE * out = fopen(argv[2], "wb");

	if (out == nullptr) {
		std::cout << "Файл для записи не может быть открыт" << std::endl;
		return 3;
	}
 
	int n = n_tests[atoi(argv[1])];// задаём размер матриц
	double ** cur = new double*[n];
	for (int i = 0; i < n; i++)
		cur[i] = new double[n];
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution <double> distribution(-100, 100);

	std::cout << "Какую матрицу сгенерировать? Введите число от 1 до 7 включительно." << std::endl;
	std::cout << 
		"1. Симметричную положительно определенную" << std::endl <<
		"2. Симметричную"							<< std::endl <<
		"3. Единичную"								<< std::endl <<
		"4. Нулевую"								<< std::endl <<
		"5. Диагональную"							<< std::endl <<
		"6. Целочисленная"							<< std::endl <<
		"7. Случайная"								<< std::endl;

	int c;//Параметр меню
	std::cin >> c;

	switch (c) {//Генерируем матрицу
	case 1: {//Симметричная положительно определенная
		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++) {
				cur[i][j] = cur[j][i] = distribution(generator);
				if (i == j)
					cur[i][j] += 400;
			}
		break;
	}
	case 2: {//Симметричная
		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++)
				cur[i][j] = cur[j][i] = distribution(generator);
		break;
	}
	case 3: {//Единичная
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cur[i][j] = 0;
				if (i == j)
					cur[i][j] = 1;
			}
		break;
	}
	case 4: {//Нулевая
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cur[i][j] = 0;
		break;
	}
	case 5: {//Диагональная
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cur[i][j] = 0;
				if (i == j)
					cur[i][j] = distribution(generator);
			}
		break;
	}
	case 6: {//Целочисленная
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cur[i][j] = (int)distribution(generator);
		break;
	}
	case 7: {//Случайная
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cur[i][j] = distribution(generator);
		break;
	}
	default: {
		std::cout << "Неверный пункт меню" << std::endl;
		fclose(out);
		for (int i = 0; i < n; i++)
			delete[] cur[i];
		delete[] cur;

		return 4;
	}
	}

	//Запись в бинарный файл
	fwrite(&n, sizeof(n), 1, out);
	for (int i = 0; i < n; i++)
		fwrite(cur[i], sizeof(**cur), n, out);

	for (int i = 0; i < n; i++)	//Генерируем вектор 
		cur[0][i] = distribution(generator);

	fwrite(cur[0], sizeof(**cur), n, out);

	//Освобождение памяти
	fclose(out);
	for (int i = 0; i < n; i++)
		delete[] cur[i];
	delete[] cur;

	return 0;
}
