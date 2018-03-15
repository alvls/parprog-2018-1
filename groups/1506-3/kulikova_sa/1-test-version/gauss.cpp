#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Sole.h"

//https://prog-cpp.ru/gauss/
void gauss(double ** a, double * b, double * x, int n) {
	double max;
	int k, index;
	const double eps = 0.00001;  // точность
	k = 0;
	while (k < n) {
		// Поиск строки с максимальным a[i][k]
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++) {
			if (abs(a[i][k]) > max) {
				max = abs(a[i][k]);
				index = i;
			}
		}
		// Перестановка строк
		if (max < eps) {
			// нет ненулевых диагональных элементов
			std::cout << "Решение получить невозможно из-за нулевого столбца " <<
				index << " матрицы A" << std::endl;
			return;
		}
		for (int j = 0; j < n; j++) {
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = b[k];
		b[k] = b[index];
		b[index] = temp;
		// Нормализация уравнений
		for (int i = k; i < n; i++) {
			double temp = a[i][k];
			if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			b[i] = b[i] / temp;
			if (i == k)  continue; // уравнение не вычитать само из себя
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			b[i] = b[i] - b[k];
		}
		k++;
	}
	// обратная подстановка
	for (k = n - 1; k >= 0; k--) {
		x[k] = b[k];
		for (int i = 0; i < k; i++)
			b[i] = b[i] - a[i][k] * x[k];
	}
}

//argv[1] - имя входного файла, argv[2] - имя выходного файла
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");// Корректное отображение Кириллицы

	if (argc != 3) {
		std::cout << "Некорректные данные" << std::endl;
		return 1;
	}

	FILE * in = fopen(argv[1], "rb");
	if (in == nullptr) {
		std::cout << "Файл для чтения не может быть открыт" << std::endl;
		return 2;
	}

	int n;
	fread(&n, sizeof(n), 1, in);

	if (n < 1) {
		std::cout << "Не положительный размер системы" << std::endl;
		fclose(in);
		return 3;
	}

	Sole * S = new Sole(n);// Создаём СЛАУ

	// Читаем из бинарника
	for (int i = 0; i < n; i++)
		fread(S->A[i], sizeof(**S->A), n, in);
	fread(S->b, sizeof(*S->b), n, in);

	fclose(in);

	gauss(S->A, S->b, S->x, S->N);

	FILE * out = fopen(argv[2], "wb");
	if (out == nullptr) {
		std::cout << "Файл для записи не может быть открыт" << std::endl;
		return 4;
	}

	//Записываем результаты в бинарник
	fwrite(S->x, sizeof(*S->x), n, out);

	fclose(out);

	return 0;
}
