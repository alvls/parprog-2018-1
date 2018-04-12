#include "CRSmatrix.h"

void CRSMatrixMult(int matrixSize, int notZeroA, double* valueA, int* colA, int* rowA, int notZeroB, double* valueB, int* colB, int* rowB,
        int& notZeroC, double*& valueC, int*& colC, int*& rowC, int threads)
{
	CRSmatrix matrixA(matrixSize, notZeroA, valueA, colA, rowA);
	CRSmatrix matrixB(matrixSize, notZeroB, valueB, colB, rowB);
	CRSmatrix matrixC = matrixA * matrixB;

	notZeroC = matrixC.getNotZero();
	valueC = matrixC.getValue();
	colC = matrixC.getCol();
	rowC = matrixC.getSparseRow();
}
