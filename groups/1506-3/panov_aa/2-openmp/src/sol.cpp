#include <omp.h>
#include <vector>
#include "matrix.h"


MatrixCCS MatrixMult(MatrixCCS &A, MatrixCCS &B)
{
    return A*B;
}

MatrixCCS ParallelMatrixMult(MatrixCCS &A, MatrixCCS &B, int numThreads)
{
	return A.parallelMult(B, numThreads);
}