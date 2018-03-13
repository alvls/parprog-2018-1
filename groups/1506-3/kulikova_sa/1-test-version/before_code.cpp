#define _CRT_SECURE_NO_WARNINGS
#include <omp.h>
#include "Sole.h"

void NonlinearConjugateGradient(Sole * S);

//Получение матрицы без i-й строки и j-го столбца
void GetMatr(double ** mas, double ** p, int i, int m) {
	int di = 0;
	for (int ki = 0; ki < m - 1; ki++) { //Проверка индекса строки
		if (ki == i) 
			di = 1;
		int dj = 0;
		for (int kj = 0; kj < m - 1; kj++) { //Проверка индекса столбца
			if (kj == 0) 
				dj = 1;
			p[ki][kj] = mas[ki + di][kj + dj];
		}
	}
}

//Рекурсивное вычисление определителя
double Determinant(double ** mas, int m) {
	double ** p = new double*[m];
	for (int i = 0; i < m; i++)
		p[i] = new double[m];
	double d = 0;
	int k = 1; //(-1) в степени i

	if (m == 1) {
		for (int i = 0; i < m; i++)
			delete[] p[i];
		delete[] p;

		return(mas[0][0]);
	}
	if (m == 2) {
		for (int i = 0; i < m; i++)
			delete[] p[i];
		delete[] p;

		return(mas[0][0] * mas[1][1] - mas[1][0] * mas[0][1]);
	}
	for (int i = 0; i < m; i++) {
		GetMatr(mas, p, i, m);
		d = d + k * mas[i][0] * Determinant(p, m - 1);
		k = -k;
	}

	for (int i = 0; i < m; i++)
		delete[] p[i];
	delete[] p;

	return(d);
}

//Размерность системы должна быть положительной, т.е N > 0
bool dimension(int N) {
	if (N < 1) {
		std::cout << "Не положительный размер системы" << std::endl;
		return true;
	}
	return false;
}

//Матрица А должна быть симетричной, т.е А=Ат
bool symmetry(double ** A, int N) {
	for (int i = 0; i < N - 1; i++)
		for (int j = i + 1; j < N; j++)
			if (A[i][j] != A[j][i]) {
				std::cout << "Матрица не симметрична" << std::endl;
				return true;
			}
	return false;
}

//Матрица А должна быть положительно определена, т.е xт*А*x > 0
bool PositiveDefinite(double ** A, int N) {
	for (int i = 1; i <= N; i++)
		if (Determinant(A, i) <= 0) {//Критерий Сильвестра
			std::cout << "Матрица не положительно определена" << std::endl;
			return true;
		}
	return false;
}

//argv[1] - количество потоков, argv[2] - имя входного файла, argv[3] - имя выходного файла
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");//Корректное отображение Кириллицы

	if (argc != 4) {
		std::cout << "Некорректные данные" << std::endl;
		return 1;
	}

	int num_threads = atoi(argv[1]);//Количество потоков
	int N;//Размер системы

	FILE * in, * out;
	in = fopen(argv[2], "rb");
	out = fopen(argv[3], "wb");
	if (in == nullptr) {
		std::cout << "Файл для чтения не может быть открыт" << std::endl;
		return 2;
	}
	if (out == nullptr) {
		std::cout << "Файл для записи не может быть открыт" << std::endl;
		return 3;
	}

	fread(&N, sizeof(N), 1, in);
	Sole * S = new Sole(N);//Создаём СЛАУ

	//Читаем из бинарника
	for (int i = 0; i < N; i++)
		fread(S->A[i], sizeof(**S->A), N, in);
	fread(S->b, sizeof(*S->b), N, in);

	fclose(in);

	if (dimension(S->N))
		return 4;
	if (symmetry(S->A, S->N))
		return 5;
	if (PositiveDefinite(S->A, S->N))
		return 6;

	omp_set_num_threads(num_threads);

	double time = omp_get_wtime();
	NonlinearConjugateGradient(S);
	time = omp_get_wtime() - time;

	//Записываем результаты в бинарник
	fwrite(&time, sizeof(time), 1, out);
	fwrite(&N, sizeof(N), 1, out);
	for (int i = 0; i < N; i++)
		fwrite(S->A[i], sizeof(**S->A), N, out);
	fwrite(S->b, sizeof(*S->b), N, out);
	fwrite(S->x, sizeof(*S->x), N, out);

	fclose(out);

	return 0;
}
