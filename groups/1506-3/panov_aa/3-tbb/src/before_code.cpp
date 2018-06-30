#include <string>
#include<iostream>
#include <vector>
#include "mymatrix.h"

using std::string;
using std::vector;

MatrixCCS MatrixMult(MatrixCCS &A, MatrixCCS &B);
MatrixCCS ParallelMatrixMult(MatrixCCS &A, MatrixCCS &B, int numThreads = 1);

int main(int argc, char * argv[])//читает из бинарного файла, запускает программу, пишет в бинарный файл
{
    string pathInput = "";
    string pathOutput = "";
	int numThreads = 1;

	if (argc > 1)
	{
        pathInput = argv[1];       
        if (argc > 2)
        {           
			pathOutput = argv[2];
            if (argc > 3)
            {
				numThreads = atoi(argv[3]);
            }
        }
	}
    
	int N;
	freopen(pathInput.c_str(), "rb", stdin);
	freopen(pathOutput.c_str(), "wb", stdout);
	fread(&N, sizeof(N), 1, stdin);
    Matrix A(N, N), B(N, N), Res(N,N);
   
    fread(A.getP(), sizeof(Element), N * N, stdin);
    fread(B.getP(), sizeof(Element), N * N, stdin);

    MatrixCCS Acol(A), Bcol(B), ResCol;

    Acol.transpositionMatrix();
    double time = omp_get_wtime();
    tbb::task_scheduler_init init(numThreads);
    ResCol = ParallelMatrixMult(Acol, Bcol, numThreads);
	time = omp_get_wtime() - time;
    Acol.transpositionMatrix();

    ResCol.convertToMatrix(Res);

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(Res.getP(), sizeof(Element), N * N, stdout);
	return 0;
}