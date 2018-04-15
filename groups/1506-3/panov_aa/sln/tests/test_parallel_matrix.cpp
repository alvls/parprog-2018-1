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
	//std::cout << res << tmp;
}

TEST(parallel_matrixCCS, can_unite)
{
	int N = 3;
	MatrixCCS m1(N), m2(N);
	m1.setValues({1.0});
	m1.setRows({1});
	m2.setValues({ 2.0 });
	m2.setRows({});
}