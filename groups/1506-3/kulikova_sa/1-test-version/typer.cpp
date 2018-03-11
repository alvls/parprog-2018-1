#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Sole.h"

//Текстовый файл преобразует в бинарный
//argv[1] - имя входного файла, argv[2] - имя выходного файла
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");//Корректное отображение Кириллицы

	if (argc != 3) {
		std::cout << "Некорректные данные" << std::endl;
		return 1;
	}

	std::ifstream in(argv[1], std::ios::in);//Открытие файла для чтения
	FILE * out;
	out = fopen(argv[2], "wb");//Открытие файла для бинарной записи

	if (!in.is_open()) {
		std::cout << "Файл для чтения не может быть открыт" << std::endl;
		return 2;
	}

	if (out == nullptr) {
		std::cout << "Файл для записи не может быть открыт" << std::endl;
		return 3;
	}

	int N;//Размер системы
	in >> N;//Считываем размер системы

	if (N < 1) {
		std::cout << "Некорректный размер системы" << std::endl;
		return 4;
	}

	fwrite(&N, sizeof(N), 1, out);
	Sole * S = new Sole(N);//Создаём СЛАУ

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			in >> S->A[i][j];//Читаем матрицу
			fwrite(&S->A[i][j], sizeof(S->A[i][j]), 1, out);
		}
	}
	for (int i = 0; i < N; i++) {
		in >> S->b[i];//Читаем столбец свободных членов
		fwrite(&S->b[i], sizeof(S->b[i]), 1, out);
	}

	in.close();//Закрытие файлов
	fclose(out);

	return 0;
}
