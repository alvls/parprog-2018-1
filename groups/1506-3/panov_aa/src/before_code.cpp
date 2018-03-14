#include <omp.h>
#include <string>
#include<iostream>
#include <vector>
#include "matrix.h"

using std::vector;
using std::string;

void MatrixMult(const MatrixCCS &A, const MatrixCCS &B, MatrixCCS &C);

int main(int argc, char * argv[])//читает из бинарного файла, запускает программу, пишет в бинарный файл
{
	int num_threads = 1;
	string name = "matr";
	string number = "";
	string extensionIn = ".in";
	string extensionOut = ".out";
	if (argc > 1)
	{
		num_threads = atoi(argv[1]);
		if (argc > 2)
		{
			number = argv[2];
		}
	}

	int N;
	freopen((name + number + extensionIn).c_str(), "rb", stdin);
	freopen((name + number + extensionOut).c_str(), "wb", stdout);
	fread(&N, sizeof(N), 1, stdin);
    Matrix A(N, N), B(N, N), C(N,N);
   
    fread(A.getP(), sizeof(Element), N * N, stdin);
    fread(B.getP(), sizeof(Element), N * N, stdin);

    MatrixCCS Acol(A), Bcol(B), Ccol(C);
    
    omp_set_num_threads(num_threads);
	
    double time = omp_get_wtime();	
    MatrixMult(Acol, Bcol, Ccol);
	time = omp_get_wtime() - time;

    Acol.convertToMatrix(A);
    Bcol.convertToMatrix(B);
    Ccol.convertToMatrix(C);

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(A.getP(), sizeof(Element), N * N, stdout);

	return 0;
}