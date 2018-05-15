#include <string>
#include<iostream>
#include <vector>
#include "matrix.h"

using std::string;
using std::vector;

MatrixCCS MatrixMult(MatrixCCS &A, MatrixCCS &B);
MatrixCCS ParallelMatrixMult(MatrixCCS &A, MatrixCCS &B, int numThreads = 1);

int main(int argc, char * argv[])//читает из бинарного файла, запускает программу, пишет в бинарный файл
{
	int num_threads = 1;
    string pathInput = "";
    string pathOutput = "";
	string name = "matr";
	string number = "";
	string extensionIn = ".in";
	string extensionOut = ".user.ans";
	if (argc > 1)
	{
        pathInput = argv[1];       
        pathOutput = pathInput + "_result/";
        pathInput += "/";
        if (argc > 2)
        {           
            number = argv[2];    
            name = "";
            if (argc > 3)
            {
                num_threads = atoi(argv[3]);
            }
        }
	}
    /*name = "\\";
    pathInput = "C:\\All\\programms\\Project\\Labs\\parprog-2018-1\\groups\\1506-3\\panov_aa\\build\\tests\\20tests";
    pathOutput = "C:\\All\\programms\\Project\\Labs\\parprog-2018-1\\groups\\1506-3\\panov_aa\\build\\tests\\20tests_result";
    number = "1";
    num_threads = 2;*/
    
	int N;
	freopen((pathInput + name + number + extensionIn).c_str(), "rb", stdin);
	freopen((pathOutput + name + number + extensionOut).c_str(), "wb", stdout);
	fread(&N, sizeof(N), 1, stdin);
    Matrix A(N, N), B(N, N), Res(N,N);
   
    fread(A.getP(), sizeof(Element), N * N, stdin);
    fread(B.getP(), sizeof(Element), N * N, stdin);

    MatrixCCS Acol(A), Bcol(B), ResCol;
    
    omp_set_num_threads(num_threads);

    Acol.transpositionMatrix();
    double time = omp_get_wtime();	
    ResCol = ParallelMatrixMult(Acol, Bcol, num_threads);
	time = omp_get_wtime() - time;
    Acol.transpositionMatrix();

    ResCol.convertToMatrix(Res);

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(Res.getP(), sizeof(Element), N * N, stdout);
	return 0;
}