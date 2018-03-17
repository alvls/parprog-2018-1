#include "../gtest/gtest/gtest.h"
#include "../../include/matrix.h"

Matrix getMatrix1()
{
    Matrix m(3, 3);
    for (int i = 0; i < m.gRow(); i++)
        m[i][0] = i + 1;
    return m;
}
Matrix getMatrix2()
{
    Matrix m(3, 3);
    for (int i = 0; i < m.gRow(); i++)
        m[i][m.gCol()-1] = i + 1;
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

TEST(matrixCCS, can_transposition)
{
    Matrix m = getMatrix1();
    TestMatrixCCS mccs(m);
    mccs.transpositionMatrix();
    mccs.transpositionMatrix();

    Matrix test(m.gRow(), m.gCol());
    mccs.convertToMatrix(test);
    EXPECT_TRUE(m == test);
}