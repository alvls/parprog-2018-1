#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <omp.h>
#include <random>
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

	for (int i = 0; i < N; i++)
		fread(S->A[i], sizeof(**S->A), N, stdin);
	fread(S->b, sizeof(*S->b), N, stdin);

	omp_set_num_threads(num_threads);

	double time = omp_get_wtime();
	NonlinearConjugateGradient(S);
	time = omp_get_wtime() - time;

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&N, sizeof(N), 1, stdout);
	for (int i = 0; i < N; i++)
		fwrite(S->A[i], sizeof(**S->A), N, stdin);
	fwrite(S->b, sizeof(*S->b), N, stdin);
	fwrite(S->x, sizeof(*S->x), N, stdout);

	return 0;
}