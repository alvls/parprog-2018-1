#include "Matrix.h"
#include "tbb\task_scheduler_init.h"
Matrix Calculate(int size, int notNull1, complex<int> *elements1, int *secondIndex1, int *position1, int notNull2, complex<int> *elements2, int *secondIndex2, int *position2, char *output, int threads_number)
{
    tbb::task_scheduler_init init(threads_number);
    Matrix matr1(size, notNull1, elements1, secondIndex1, position1), matr2(size, notNull2, elements2, secondIndex2, position2);
    return matr1 * matr2;
}

