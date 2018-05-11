#include "CRSmatrix.h"
#include "tbb/task_scheduler_init.h"

void CRSMatrixMult(CRSmatrix &matrixA, CRSmatrix &matrixB, CRSmatrix &matrixC, int threads)
{
	tbb::task_scheduler_init init(threads);
	
	matrixC = matrixA * matrixB;
}
