#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Sole.h"

//Отображает бинарный файл
//argv[1] - имя входного файла
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");//Корректное отображение Кириллицы

	if (argc != 2) {
		std::cout << "Некорректные данные" << std::endl;
		return 1;
	}

	FILE * in;
	in = fopen(argv[1], "rb");//Открытие файла для бинарного чтения

	if (in == nullptr) {
		std::cout << "Файл для чтения не может быть открыт" << std::endl;
		return 2;
	}

	int N;//Размер системы
	double time;//Время работы

	fread(&time, sizeof(time), 1, in);
	fread(&N, sizeof(N), 1, in);

	Sole * S = new Sole(N);//Создаём СЛАУ

	for (int i = 0; i < N; i++)
		fread(S->A[i], sizeof(**S->A), N, in);
	fread(S->b, sizeof(*S->b), N, in);
	fread(S->x, sizeof(*S->x), N, in);

	fclose(in);

	std::cout << "Время работы " << time << std::endl;
	S->Print();

	return 0;
}
