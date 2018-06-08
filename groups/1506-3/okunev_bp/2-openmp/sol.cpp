#include "CRSmatrix.h"
#include <omp.h>

void CRSMatrixMult(CRSmatrix &matrixA, CRSmatrix &matrixB, CRSmatrix &matrixC, int threads)
{
	omp_set_num_threads(threads);
	
	matrixC = matrixA * matrixB;
}
