#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include <iostream>

using namespace std;
// ������� ������ ����� ������������� ����������� ��������� � �������
int n_tests[] = { 1, 2, 3, 5, 7, 8, 9, 10, 10, 1000, 10000, 10000, 10000, 500000, 100000, 1000000, 10000000, 25000000, 50000000, 100000000 };

int main(int argc, char * argv[]) {
	// �� ���� ������ ���������� ���� ����� � ��������� �� [0,20] � ����� ������������ �����
	if (argc != 2 || atoi(argv[1]) < 1 || atoi(argv[1]) > 20) return 0;
	// ���������� ����������� ������ �������
	int n = n_tests[atoi(argv[1]) - 1];
	// ������ ����(��� �������������� ���� �� ����������) � ������� ����� ���������� ��������� ������ ���������
	freopen(argv[1], "wt", stdout);
	// ������ ��������� ��������� ����� � seed ������ ���������� ������� � ������ �����
	default_random_engine generator(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
	// ������ ����������� ������������� ��������� �������� ���� double � ��������� [-10000, 10000] 
	uniform_real_distribution <double> distribution(-1e4, 1e4);
	// ���������� ���-�� ��������� �������
	fwrite(&n, sizeof(n), 1, stdout);

	double *values = new double[n];
	// ���������� ������� ����������� ����������
	if (n == 12) {
		double value = distribution(generator);
		for (int i = 0; i < n; i++)
			values[i] = value;
	}
	else
		// ���������� ������� �� �������������
		if (n == 13) {
			double value = distribution(generator);
			for (int i = 0; i < n; i++)
				values[i] = value - i;
		}
		else
			// ���������� ������� �� �� ��������
			if (n == 14) {
				double value = distribution(generator);
				for (int i = 0; i < n; i++)
					values[i] = value + i;
			}
			else
				// ���������� ������� ���������� ���������� ���� double � ��������� �� [-10000, 10000] 
				for (int i = 0; i < n; i++) {
					values[i] = distribution(generator);
					cout << values[i] << endl;
				}
	// ������ ������� � ����
	fwrite(values, sizeof(*values), n, stdout);
	return 0;
}