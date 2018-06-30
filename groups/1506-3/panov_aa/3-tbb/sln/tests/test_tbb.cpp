#include "../gtest/gtest/gtest.h"
#include "tbb/tbb.h"
#include "mymatrix.h"

void Foo(int &a)
{
    a++;
}
void ParallelApplyFoo(int *a, size_t n) 
{
    tbb::parallel_for(size_t(0), n, size_t(1), [=](size_t i) { Foo(a[i]); });
}
TEST(tbb_test, tbb_work)
{
    tbb::task_scheduler_init init(4);
    std::vector<int> ar(10000);
    ParallelApplyFoo(&ar[0], ar.size());
    int numbers_of_1 = std::count(ar.begin(), ar.end(), 1);
    EXPECT_EQ(numbers_of_1, ar.size());
}


TEST(tbb_test, can_parallel_mult1)
{
    tbb::task_scheduler_init init(2);

    int N = 5;
    Matrix m1 = Matrix(N, N), m2(N, N), tmp(N, N);
    m1.vv = { -5, 0, 0, 0, 0,
        0, 0, 0, 5, 0,
        0, 0, 0, 9, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0 };

    m2.vv = { 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 10,
        0, 7, 2, 0, -2,
        0, 0, 0, 0, 0 };
    Matrix res = m1*m2;
    MatrixCCS mccs1(m1), mccs2(m2);
    mccs1.transpositionMatrix();

    MatrixCCS resCCS = mccs1.parallelMult(mccs2, 4);

    resCCS.convertToMatrix(tmp);
    EXPECT_TRUE(res == tmp);
}