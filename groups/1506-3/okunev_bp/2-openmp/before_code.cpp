#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <chrono>
#include <iostream>
#include "CRSmatrix.h"

using std::chrono::steady_clock;

using std::cout;
using std::cin;

void CRSMatrixMult(CRSmatrix &matrixA, CRSmatrix &matrixB, CRSmatrix &matrixC, int threads);

int main(int argc, char * argv[]) {
	char* PATHin = "matr.in";
	char* PATHout = "matr.out";
	int num_threads = 1;

	if (argc > 1)
	{
		num_threads = atoi(argv[1]);
		if (argc > 2) 
		{
			PATHin = argv[2];
			if (argc > 3)
			PATHout = argv[3];
		}
	}

	freopen(PATHin, "rb", stdin);
	freopen(PATHout, "wb", stdout);

	int sizeA;
	int NotZeroA;
	double* valueA;
	int* colA;
	int* rowA;

	int sizeB;
	int NotZeroB;
	double* valueB;
	int* colB;
	int* rowB;

	int sizeC = 0;
	int NotZeroC = 0;
	double* valueC;
	int* colC;
	int* rowC;

	//input A matrix
	fread(&sizeA, sizeof(sizeA), 1, stdin);
	fread(&NotZeroA, sizeof(NotZeroA), 1, stdin);

	valueA = new double[NotZeroA];
	colA = new int[NotZeroA];
	rowA = new int[sizeA + 1];

	fread(valueA, sizeof(*valueA), NotZeroA, stdin);
	fread(colA, sizeof(*colA), NotZeroA, stdin);
	fread(rowA, sizeof(*rowA), sizeA + 1, stdin);
	
	//input B matrix
	fread(&sizeB, sizeof(sizeB), 1, stdin);
	fread(&NotZeroB, sizeof(NotZeroB), 1, stdin);

	valueB = new double[NotZeroB];
	colB = new int[NotZeroB];
	rowB = new int[sizeB + 1];

	fread(valueB, sizeof(*valueB), NotZeroB, stdin);
	fread(colB, sizeof(*colB), NotZeroB, stdin);
	fread(rowB, sizeof(*rowB), sizeB + 1, stdin);

	//create matrix
	CRSmatrix matrixA(sizeA, NotZeroA, valueA, colA, rowA);
	delete[] valueA;
	delete[] colA;
	delete[] rowA;
	CRSmatrix matrixB(sizeB, NotZeroB, valueB, colB, rowB);
	delete[] valueB;
	delete[] colB;
	delete[] rowB;
	CRSmatrix matrixC;


	steady_clock::time_point start = steady_clock::now();
	CRSMatrixMult(matrixA, matrixB, matrixC, num_threads);
	steady_clock::time_point end = steady_clock::now();

	double time = std::chrono::duration_cast<std::chrono::microseconds>
		(end - start).count();

	//get result
	NotZeroC = matrixC.getNotZero();
	valueC = matrixC.getValue();
	colC = matrixC.getCol();
	rowC = matrixC.getSparseRow();

	//output C matrix
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&sizeA, sizeof(sizeA), 1, stdout);
	fwrite(&NotZeroC, sizeof(NotZeroC), 1, stdout);
	fwrite(valueC, sizeof(*valueC), NotZeroC, stdout);
	fwrite(colC, sizeof(*colC), NotZeroC, stdout);
	fwrite(rowC, sizeof(*rowC), sizeA + 1, stdout);


	delete[] valueC;
	delete[] colC;
	delete[] rowC;

	return 0;
}

