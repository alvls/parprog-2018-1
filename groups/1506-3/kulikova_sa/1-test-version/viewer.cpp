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

	FILE * out;
	out = fopen(argv[1], "rb");//Открытие файла для бинарного чтения

	int N;//Размер системы
	double time;//Время работы

	fread(&time, sizeof(time), 1, out);
	fread(&N, sizeof(N), 1, out);

	Sole * S = new Sole(N);//Создаём СЛАУ

	for (int i = 0; i < N; i++)
		fread(S->A[i], sizeof(**S->A), N, out);
	fread(S->b, sizeof(*S->b), N, out);
	fread(S->x, sizeof(*S->x), N, out);

	std::cout << "Время работы " << time << std::endl;
	S->Print();

	return 0;
}
