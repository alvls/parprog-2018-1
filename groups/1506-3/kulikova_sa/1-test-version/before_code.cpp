#define _CRT_SECURE_NO_WARNINGS
#include <omp.h>
#include "Sole.h"

void NonlinearConjugateGradient(Sole * S);
void NonlinearConjugateGradient_OMP(Sole * S, int num);
void NonlinearConjugateGradient_TBB(Sole * S, int num);

// ��������� ������� ��� i-� ������ � j-�� �������
void GetMatr(double ** mas, double ** p, int i, int m) {
	int di = 0;
	for (int ki = 0; ki < m - 1; ki++) { // �������� ������� ������
		if (ki == i) 
			di = 1;
		int dj = 0;
		for (int kj = 0; kj < m - 1; kj++) { // �������� ������� �������
			if (kj == 0) 
				dj = 1;
			p[ki][kj] = mas[ki + di][kj + dj];
		}
	}
}

// ����������� ���������� ������������
double Determinant(double ** mas, int m) {
	double ** p = new double*[m];
	for (int i = 0; i < m; i++)
		p[i] = new double[m];
	double d = 0;
	int k = 1; // (-1) � ������� i

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

// ����������� ������� ������ ���� �������������, �.� N > 0
bool dimension(int N) {
	if (N < 1) {
		std::cout << "�� ������������� ������ �������" << std::endl;
		return true;
	}
	return false;
}

// ������� � ������ ���� �����������, �.� �=��
bool symmetry(double ** A, int N) {
	for (int i = 0; i < N - 1; i++)
		for (int j = i + 1; j < N; j++)
			if (A[i][j] != A[j][i]) {
				std::cout << "������� �� �����������" << std::endl;
				return true;
			}
	return false;
}

// ������� � ������ ���� ������������ ����������
bool PositiveDefinite(double ** A, int N) {
	if (N < 11) {// �������� ����������
		for (int i = 1; i <= N; i++)
			if (Determinant(A, i) <= 0) {
				std::cout << "������� �� ������������ ����������" << std::endl;
				return true;
			}
	}
	else {// ������������ ������������ 
		for (int i = 0; i < N; i++) {
			double res = 0;
			for (int j = 0; j < N; j++) {
				if (i != j)
					res += A[i][j];
			}
			if (res > A[i][i]) {
				std::cout << "������� �� ������������ ����������" << std::endl;
				return true;
			}
		}
	}
	return false;
}

// argv[1] - ���������� �������, argv[2] - ��� �������� �����, argv[3] - ��� ��������� �����
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");// ���������� ����������� ���������

	if (argc != 4) {
		std::cout << "������������ ������" << std::endl;
		return 1;
	}

	int num_threads = atoi(argv[1]);// ���������� �������
	int N;// ������ �������

	FILE * in = fopen(argv[2], "rb");
	if (in == nullptr) {
		std::cout << "���� ��� ������ �� ����� ���� ������" << std::endl;
		return 2;
	}

	fread(&N, sizeof(N), 1, in);

	if (N < 1) {
		std::cout << "�� ������������� ������ �������" << std::endl;
		fclose(in);
		return 3;
	}

	Sole * S = new Sole(N);// ������ ����

	// ������ �� ���������
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

	std::cout << "����� ������ ��������� ��������� :"
		<< std::endl << "1. ����������������"
		<< std::endl << "2. OpenMP"
		<< std::endl << "3. TBB"
		<< std::endl;

	double time = 0;
	int menu = 1;
	std::cin >> menu;

	switch (menu)
	{
	case 1: {
		time = omp_get_wtime();
		NonlinearConjugateGradient(S);
		time = omp_get_wtime() - time;
		break;
	}
	case 2: {
		time = omp_get_wtime();
		NonlinearConjugateGradient_OMP(S, num_threads);
		time = omp_get_wtime() - time;
		break;
	}
	case 3: {
		time = omp_get_wtime();
		NonlinearConjugateGradient_TBB(S, num_threads);
		time = omp_get_wtime() - time;
		break;
	}
	default:
		break;
	}

	FILE * out = fopen(argv[3], "wb");
	if (out == nullptr) {
		std::cout << "���� ��� ������ �� ����� ���� ������" << std::endl;
		return 7;
	}

	// ���������� ���������� � ��������
	fwrite(&time, sizeof(time), 1, out);
	fwrite(&N, sizeof(N), 1, out);
	for (int i = 0; i < N; i++)
		fwrite(S->A[i], sizeof(**S->A), N, out);
	fwrite(S->b, sizeof(*S->b), N, out);
	fwrite(S->x, sizeof(*S->x), N, out);

	fclose(out);

	return 0;
}