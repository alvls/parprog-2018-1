#include <omp.h>
#include <vector>
#include "matrix.h"


void MatrixMult(const MatrixCCS &A, const MatrixCCS &B, MatrixCCS &C)
{

}

/*void MatrMatrMult(double * A, double * B, double * C, int N)
{
	int i, j, k;
#pragma omp parallel for private(j, k)
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			C[i * N + j] = 0.0;
			for (k = 0; k < N; k++)
				C[i * N + j] += A[i * N + k] * B[k * N + j];
		}
	}
}*/