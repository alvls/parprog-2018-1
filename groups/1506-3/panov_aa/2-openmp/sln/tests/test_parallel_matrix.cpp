#include "../gtest/gtest/gtest.h"
#include "../../include/matrix.h"

Matrix getMatrix6()
{
	Matrix m(3, 3);
	for (int i = 0; i < m.gRow(); i++)
		m[0][i] = i + 1;
	return m;
}
Matrix getMatrix7()
{
	Matrix m(3, 3);
	for (int j = 0; j < m.gCol(); j++)
		m[j][m.gRow() - 1] = j + 1;
	return m;
}
TEST(parallel_matrixCCS, can_test_mult1)
{
	Matrix m1 = getMatrix6();
	Matrix m2 = getMatrix7();

	MatrixCCS mccs1(m1);
	MatrixCCS mccs2(m2);

	MatrixCCS resCCS = mccs1.testMult(mccs2);

	Matrix res = m1*m2;
	Matrix tmp(3, 3);
	resCCS.convertToMatrix(tmp);
	EXPECT_TRUE(res == tmp);
}

TEST(parallel_matrixCCS, can_test_mult2)
{
    int N = 5;
    Matrix m1 = Matrix(N, N), m2(N, N), tmp(N, N);
    m1.vv = 
    {0, 1, 2, 0, 3,
     0, 0, 0, 0, 0,
     4, 5, 0, 0, 0,
     6, 7, 8, 0, 10,
     0, 0, 11, 0, 12};
    m2.vv = m1.vv;
    m2.transpositionMatrix();
    Matrix res = m1*m2;
    std::cout << res;
    MatrixCCS mccs1(m1), mccs2(m2);
    MatrixCCS resCCS = mccs1.testMult(mccs2, 5);

    resCCS.convertToMatrix(tmp);
    std::cout << tmp;
    EXPECT_TRUE(res == tmp);
}

TEST(parallel_matrixCCS, can_test_mult3)
{
    int N = 5;
    Matrix m1 = Matrix(N, N), m2(N, N), tmp(N, N);
    m1.vv = vector<Element>(N*N);
    m2.vv = vector<Element>(N*N);
    Matrix res = m1*m2;
    std::cout << res;
    MatrixCCS mccs1(m1), mccs2(m2);
    MatrixCCS resCCS = mccs1.testMult(mccs2, 5);

    resCCS.convertToMatrix(tmp);
    std::cout << tmp;
    EXPECT_TRUE(res == tmp);
}

TEST(parallel_matrixCCS, can_unite)
{
	int N = 3;
	MatrixCCS m1(N), m2(N), m3(N), res(N);
	m1.setValues({1.0});
	m1.setRows({1});
    m1.setPointer({0, 1});

	m2.setValues({ 2.0 });
	m2.setRows({0});
    m2.setPointer({ 0, 1});

    m3.setValues({ 5.0, 3.0 });
    m3.setRows({ 1, 2 });
    m3.setPointer({ 0, 2 });

    res.setValues({1.0, 2.0, 5.0, 3.0 });
    res.setRows({ 1, 0, 1, 2 });
    res.setPointer({ 0, 1, 2, 4 });

    m1.unite(m2);
    m1.unite(m3);
    
    EXPECT_TRUE(m1 == res);
}

TEST(parallel_matrixCCS, can_mult4)
{
    int N = 5;
    Matrix m1 = Matrix(N, N), m2(N, N), tmp(N, N);
    m1.vv = { -5, 0, 0, 0, 0,
               0, 0, 0, 5, 0,
               0, 0, 0, 9, 0,
               0, 0, 0, 0, 0,
               0, 0, 0, 0, 0 };

    m2.vv = {  0, 0, 0, 0, 0,
               0, 0, 0, 0, 0,
               0, 0, 0, 0, 10,
               0, 7, 2, 0, -2,
               0, 0, 0, 0, 0 };
    Matrix res = m1*m2;
    std::cout << res;
    MatrixCCS mccs1(m1), mccs2(m2);
    MatrixCCS resCCS = mccs1.testMult(mccs2, 5);

    resCCS.convertToMatrix(tmp);
    std::cout << tmp;
    EXPECT_TRUE(res == tmp);
}

TEST(parallel_matrixCCS, can_mult5)
{
    int N = 7;
    Matrix m1 = Matrix(N, N), m2(N, N), tmp(N, N);
    m1.vv = { 0.346812, - 5.8216, 0, 0.50235, - 3.72964, 0, 5.86558,
        3.57657, 4.52315, 9.08149, 1.00769, - 0.715764, 0, 7.08229,
        8.88401, - 2.333 ,- 8.72146, 9.42538, 9.83971, - 7.83694, - 2.82068,
        - 7.23858, - 2.95456, - 6.92518, 0, 3.55216, 0.481534, 2.77139,
        0, 0, 4.53356, 0, 2.50495, - 4.78534, 0,
        - 0.0128143, - 8.03703, 1.8011, - 7.91007, 3.1875, 0, 5.64586,
        6.83576, - 1.00743, 9.5144, 2.58616, - 7.56072, 6.31918, - 6.73807 };

    m2.vv = { 5.56512, - 6.07813, - 9.93718 ,2.74813, - 1.25525, 3.57945 ,- 8.87455,
        3.61921, 0.749451 ,- 0.3347 ,3.686 ,- 0.597627 ,2.6045, - 7.49067,
        1.74408, 0, - 5.22637, 6.96284, -4.33531, - 4.42203, 7.27609,
        3.96794, - 6.64085, - 4.39155, - 9.86812, 6.26412, - 7.31571, 0,
        - 5.57667, 9.5829 ,- 0.661448, 0, 0, 0, - 9.42076,
        - 2.673, 0, 9.70597, 4.48116, - 7.50321, - 6.6405, 6.80723,
        8.50821, 9.09021, 9.24417, 0, 0, 0, 8.89995 };
    Matrix res = m1*m2;
    std::cout << res;
    MatrixCCS mccs1(m1), mccs2(m2);
    MatrixCCS resCCS = mccs1.testMult(mccs2, 4);

    resCCS.convertToMatrix(tmp);
    std::cout << tmp;
    EXPECT_TRUE(res == tmp);
}