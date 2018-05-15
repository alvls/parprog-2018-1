#include <omp.h>
#include <string>
#include<iostream>
#include <vector>
#include "matrix.h"

using std::vector;
using std::string;

MatrixCCS MatrixMult(MatrixCCS &A, MatrixCCS &B);

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

	int N;
	freopen((pathInput + name + number + extensionIn).c_str(), "rb", stdin);
	freopen((pathOutput + name + number + extensionOut).c_str(), "wb", stdout);
	fread(&N, sizeof(N), 1, stdin);
    Matrix A(N, N), B(N, N), Res(N,N);
   
    fread(A.getP(), sizeof(Element), N * N, stdin);
    fread(B.getP(), sizeof(Element), N * N, stdin);

    MatrixCCS Acol(A), Bcol(B), ResCol;
    
    omp_set_num_threads(num_threads);
	
    double time = omp_get_wtime();	
    ResCol = MatrixMult(Acol, Bcol);
	time = omp_get_wtime() - time;

    ResCol.convertToMatrix(Res);

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(Res.getP(), sizeof(Element), N * N, stdout);
	return 0;
}