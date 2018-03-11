#define _CRT_SECURE_NO_WARNINGS
#include <omp.h>
#include "Sole.h"

void NonlinearConjugateGradient(Sole * S);

//argv[1] - количество потоков, argv[2] - имя входного файла, argv[3] - имя выходного файла
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");//Корректное отображение Кириллицы

	if (argc != 4) {
		std::cout << "Некорректные данные" << std::endl;
		return 1;
	}

	int num_threads = atoi(argv[1]);//Количество потоков
	int N;//Размер системы

	freopen(argv[2], "rb", stdin);
	freopen(argv[3], "wb", stdout);

	fread(&N, sizeof(N), 1, stdin);

	Sole * S = new Sole(N);//Создаём СЛАУ

	//Читаем из бинарника
	for (int i = 0; i < N; i++)
		fread(S->A[i], sizeof(**S->A), N, stdin);
	fread(S->b, sizeof(*S->b), N, stdin);

	//Размерность системы должна быть положительной, т.е N > 0
	if (S->N < 1) {
		std::cout << "Не положительный размер системы" << std::endl;
		return 2;
	}
	//Матрица А должна быть симетричной, т.е А=Ат
	for (int i = 0; i < S->N - 1; i++)
		for (int j = i + 1; j < S->N; j++)
			if (S->A[i][j] != S->A[j][i]) {
				std::cout << "Матрица не симметрична" << std::endl;
				return 3;
			}
	//Матрица А должна быть положительно определена, т.е xт*А*x > 0
	if (false) {//КАК??? Критерий Сильвестра???
		std::cout << "Матрица не положительно определена" << std::endl;
		return 4;
	}

	omp_set_num_threads(num_threads);

	double time = omp_get_wtime();
	NonlinearConjugateGradient(S);
	time = omp_get_wtime() - time;

	//Записываем результаты в бинарник
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&N, sizeof(N), 1, stdout);
	for (int i = 0; i < N; i++)
		fwrite(S->A[i], sizeof(**S->A), N, stdout);
	fwrite(S->b, sizeof(*S->b), N, stdout);
	fwrite(S->x, sizeof(*S->x), N, stdout);

	return 0;
}
