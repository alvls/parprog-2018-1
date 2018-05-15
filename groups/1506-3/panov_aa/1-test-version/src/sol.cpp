#include <omp.h>
#include <vector>
#include "matrix.h"


MatrixCCS MatrixMult(MatrixCCS &A, MatrixCCS &B)
{
    return A*B;
}