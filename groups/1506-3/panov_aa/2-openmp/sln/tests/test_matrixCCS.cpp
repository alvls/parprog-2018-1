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
    for (int i = 0; i < m.gRow(); i++)
        m[0][i] = i + 1;
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
Matrix getMatrix4()
{
    Matrix m(3, 3);
    m[0][0] = 5;
    m[0][1] = -1;
    m[0][2] = 2;

    m[1][0] = 3;
    m[1][1] = 6;
    m[1][2] = -4;

    m[2][0] = -7;
    m[2][1] = -3;
    m[2][2] = 1;
    return m;
}
Matrix getMatrix5()
{
    Matrix m(3, 3);
    m[0][0] = 4;
    m[0][1] = 4;
    m[0][2] = 2;

    m[1][0] = -1;
    m[1][1] = -2;
    m[1][2] = 0;

    m[2][0] = 3;
    m[2][1] = -6;
    m[2][2] = 3;
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
    Matrix tmp(m1.gCol(), m1.gRow());
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
    //std::cout << res << tmp;
}

TEST(matrixCCS, can_mult3)
{
    Matrix m1 = getMatrix4();
    Matrix m2 = getMatrix5();

    MatrixCCS mccs1(m1);
    MatrixCCS mccs2(m2);

    MatrixCCS resCCS = mccs1*mccs2;

    Matrix res = m1*m2;
    Matrix tmp(3, 3);
    resCCS.convertToMatrix(tmp);
    EXPECT_TRUE(res == tmp);
    //std::cout << res << tmp;
}

TEST(matrixCCS, can_mult4)
{
    Matrix m1 = getMatrix5();
    Matrix m2 = getMatrix4();

    MatrixCCS mccs1(m1);
    MatrixCCS mccs2(m2);

    MatrixCCS resCCS = mccs1*mccs2;

    Matrix res = m1*m2;
    Matrix tmp(3, 3);
    resCCS.convertToMatrix(tmp);
    EXPECT_TRUE(res == tmp);
    //std::cout << res << tmp;
}

TEST(matrixCCS, can_mult5)
{
    Matrix m1 = getMatrix3();
    Matrix m2 = getMatrix4();

    MatrixCCS mccs1(m1);
    MatrixCCS mccs2(m2);

    MatrixCCS resCCS = mccs1*mccs2;

    Matrix res = m1*m2;
    Matrix tmp(3, 3);
    resCCS.convertToMatrix(tmp);
    EXPECT_TRUE(res == tmp);
    //std::cout << res << tmp;
}

TEST(matrixCCS, can_mult6)
{
    int N = 5;
    Matrix m1(N,N), m2(N,N), tmp(N,N), res;
    m1.vv =
    { 0, 1, 2, 0, 3,
        0, 0, 0, 0, 0,
        4, 5, 0, 0, 0,
        6, 7, 8, 0, 10,
        0, 0, 11, 0, 12 };
    m2.vv = m1.vv;
    m2.transpositionMatrix();

    MatrixCCS mccs1(m1);
    MatrixCCS mccs2(m2);

    MatrixCCS resCCS = mccs1*mccs2;
    res = m1*m2;

    resCCS.convertToMatrix(tmp);
    EXPECT_TRUE(res == tmp);
    //std::cout << res << tmp;
}