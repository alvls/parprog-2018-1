#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

//Отображение выходного файла
int viewer(int argc, char * argv[]) {
	if (argc != 3) {
		std::cout << "Некорректные данные" << std::endl;
		return 1;
	}

	int N;
	double **A, *b, *x;

	freopen(argv[1], "rb", stdin);

	fread(&N, sizeof(N), 1, stdin);

	A = new double*[N];
	for (int i = 0; i < N; i++)
		A[i] = new double[N];
	b = new double[N];
	x = new double[N];

	for (int i = 0; i < N; i++)
		fread(A[i], sizeof(**A), N, stdin);
	fread(b, sizeof(*b), N, stdin);
	fread(x, sizeof(*x), N, stdin);

	std::cout << "Матрица системы" << std::endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			std::cout << A[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << "Столбец свободных членов" << std::endl;
	for (int i = 0; i < N; i++) {
		std::cout << b[i] << " ";
	}
	std::cout << std::endl << "Столбец решения" << std::endl;
	for (int i = 0; i < N; i++) {
		std::cout << x[i] << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < N; i++)
		delete[] A[i];
	delete[] A;
	delete[] b;
	delete[] x;

	return 0;
}