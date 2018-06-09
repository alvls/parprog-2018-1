#include <cstdio>
#include <omp.h> 
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

void MatrMatrMult(double* A[], double* B[], double* C[], int N, int sizeBlock);
void StringName_to_CharName(string str, char* ch);


int main(int argc, char * argv[]) 
{
	int num_threads = 1;

	if (argc > 1)
		num_threads = atoi(argv[1]);

	int N, sizeBlock;

	FILE *matr_in, *matr_out;

	// Имена файлов
	char* fileName = "matr.in";
	char* answerName = "matr.out";

	if (argc > 2)
	{
		// Формируем новое имя файла с матрицами
		fileName = argv[2];
		// Формируем новое имя выходного файла
		string str = string(argv[2]) + string(".out");
		answerName = new char[str.length()];
		StringName_to_CharName(str, answerName);
		//answerName = argv[3];
	}

	freopen_s(&matr_in, fileName, "rb", stdin);

	fread(&N, sizeof(N), 1, stdin);
	fread(&sizeBlock, sizeof(sizeBlock), 1, stdin);

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


	for (int i = 0; i < N; i++)
	{
		fread(A[i], sizeof(double), N, stdin);
	}
	for (int i = 0; i < N; i++)
	{
		fread(B[i], sizeof(double), N, stdin);
	}

	fclose(matr_in);


	omp_set_num_threads(num_threads);

	double time = omp_get_wtime();
	MatrMatrMult(A, B, C, N, sizeBlock);
	time = omp_get_wtime() - time;

	//cout << num_threads << endl;
	//std::cout << time << std::endl;
	
	freopen_s(&matr_out, answerName, "wb", stdout);

	for (int i = 0; i < N; i++)
	{
		// записываем строку в бинарном виде в файл
		fwrite(C[i], sizeof(double), N, stdout);
	}
	fwrite(&time, sizeof(time), 1, stdout);

	fclose(matr_out);

	return 0;
}

void StringName_to_CharName(string str, char* ch)
{
	for (int i = 0; i < str.length(); i++)
		ch[i] = str[i];
}