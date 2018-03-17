#include "../gtest/gtest/gtest.h"
#include "../../include/matrix.h"
/*
1 2 3
0 0 0
0 0 0

rows 0 0 0
pointer 0 1 2 3 4
*/
Matrix getMatrix1()
{
    Matrix m(3, 3);
    for (int j = 0; j < m.gCol(); j++)
        m[j][0] = j + 1;
    return m;
}
Matrix getMatrix2()
{
    Matrix m(3, 3);
    for (int j = 0; j < m.gCol(); j++)
        m[j][m.gRow()-1] = j + 1;
    return m;
}
Matrix getMatrix3()
{
    Matrix m(3, 3);
    for (int j = 0; j < m.gCol(); j++)
        m[j][j] = j + 1;
    m[2][0] = 10;
    return m;
}
class TestMatrixCCS : public MatrixCCS
{
public:
    TestMatrixCCS(Matrix &m) : MatrixCCS(m){}
    void setValues(vector<Element> v)
    {
        values = v;
    }
    void setRows(vector<int> v)
    {
        rows = v;
    }
    void setPointer(vector<int> v)
    {
        pointer = v;
    }
};

TEST(matrixCCS, can_convert1)
{
    Matrix m = getMatrix1();
    TestMatrixCCS mccs(m);
    Matrix test(m.gRow(), m.gCol());
    mccs.convertToMatrix(test);
    EXPECT_TRUE(m == test);
}

TEST(matrixCCS, can_convert2)
{
    Matrix m = getMatrix2();
    TestMatrixCCS mccs(m);
    Matrix test(m.gRow(), m.gCol());
    mccs.convertToMatrix(test);
    EXPECT_TRUE(m == test);
}

TEST(matrixCCS, can_convert3)
{
    Matrix m = getMatrix3();
    TestMatrixCCS mccs(m);
    Matrix test(m.gRow(), m.gCol());
    mccs.convertToMatrix(test);
    EXPECT_TRUE(m == test);
}

TEST(matrixCCS, can_transposition1)
{
    Matrix m = getMatrix1();
    TestMatrixCCS mccs(m);
    mccs.transpositionMatrix();
    mccs.transpositionMatrix();

    Matrix test(m.gRow(), m.gCol());
    mccs.convertToMatrix(test);
    EXPECT_TRUE(m == test);
}

TEST(matrixCCS, can_transposition2)
{
    Matrix m = getMatrix2();
    TestMatrixCCS mccs(m);
    mccs.transpositionMatrix();
    mccs.transpositionMatrix();

    Matrix test(m.gRow(), m.gCol());
    mccs.convertToMatrix(test);
    EXPECT_TRUE(m == test);
}

TEST(matrixCCS, can_transposition3)
{
    Matrix m = getMatrix1();
    TestMatrixCCS mccs(m);
    mccs.transpositionMatrix();

    Matrix test(m.gRow(), m.gCol());
    mccs.convertToMatrix(test);
    test.transpositionMatrix();
    EXPECT_TRUE(m == test);
}

TEST(matrixCCS, can_mult1)
{
    Matrix m1 = getMatrix1();
    MatrixCCS mccs1(m1);
    MatrixCCS mccs2(m1);
    MatrixCCS res = mccs1*mccs2;
    Matrix tmp = getMatrix1();
    res.convertToMatrix(tmp);
    EXPECT_TRUE(m1 == tmp);
}

TEST(matrixCCS, can_mult2)
{
    Matrix m1 = getMatrix1();
    Matrix m2 = getMatrix3();

    MatrixCCS mccs1(m1);
    MatrixCCS mccs2(m2);
    MatrixCCS resCCS = mccs1*mccs2;
    Matrix res = m1*m2;
    Matrix tmp(3,3);
    resCCS.convertToMatrix(tmp);
    EXPECT_TRUE(res == tmp);
    std::cout << res << tmp;
}