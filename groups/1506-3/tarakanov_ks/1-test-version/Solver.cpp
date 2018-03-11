#include <cstdio>
#include <random>
#include <iostream>
#include <windows.h>
#include <chrono>
#include <random>
#include <string>

using namespace std;

void MatrMulti(double* A[], double* B[], double* C[], int N);
void StringName_to_CharName(string str, char* ch);

int main(int argc, char * argv[])
{
	int N, sizeBlock;

	FILE *matr_in, *matr_out;

	// ����� ������
	char* fileName = "matr.in";
	char* answerName = "matr.out";

	if (argc > 1)
	{
		// ��������� ����� ��� ����� � ���������
		fileName = argv[1];
		// ��������� ����� ��� ��������� �����
		string str = string(argv[1]) + string(".out");
		answerName = new char[str.length()];
		StringName_to_CharName(str, answerName);
	}

	freopen_s(&matr_in, fileName, "rb", stdin);

	// ��������� ������� ������
	fread(&N, sizeof(N), 1, stdin);
	fread(&sizeBlock, sizeof(sizeBlock), 1, stdin);

	// ��������� ������ ��� ������
	double **A = new double*[N];
	for (int count = 0; count < N; count++)
		A[count] = new double[N];

	double **B = new double*[N];
	for (int count = 0; count < N; count++)
		B[count] = new double[N];

	double **C = new double*[N];
	for (int count = 0; count < N; count++)
		C[count] = new double[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			C[i][j] = 0;
		}

	// ���������� ������ A � B
	for (int i = 0; i < N; i++)
	{
		fread(A[i], sizeof(double), N, stdin);
	}
	for (int i = 0; i < N; i++)
	{
		fread(B[i], sizeof(double), N, stdin);
	}

	fclose(matr_in);

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	// ���������������� ��������� ������
	MatrMulti(A, B, C, N);
	end = std::chrono::system_clock::now();

	double time = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

	freopen_s(&matr_out, answerName, "wb", stdout);

	// ������ ������ ����������
	for (int i = 0; i < N; i++)
	{
		// ���������� ������ � �������� ���� � ����
		fwrite(C[i], sizeof(double), N, stdout);
	}

	fwrite(&time, sizeof(time), 1, stdout);

	fclose(matr_out);

	return 0;
}

void MatrMulti(double* A[], double* B[], double* C[], int N)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
}

void StringName_to_CharName(string str, char* ch)
{
	for (int i = 0; i < str.length(); i++)
		ch[i] = str[i];
}