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

	freopen(argv[1], "rb", stdin);//Открытие файла для бинарного чтения

	int N;//Размер системы
	double time;//Время работы

	fread(&time, sizeof(time), 1, stdin);
	fread(&N, sizeof(N), 1, stdin);

	Sole * S = new Sole(N);//Создаём СЛАУ

	for (int i = 0; i < N; i++)
		fread(S->A[i], sizeof(**S->A), N, stdin);
	fread(S->b, sizeof(*S->b), N, stdin);
	fread(S->x, sizeof(*S->x), N, stdin);

	std::cout << "Время работы " << time << std::endl;
	S->Print();

	return 0;
}