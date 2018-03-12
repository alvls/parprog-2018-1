#pragma once
#include <vector>
#include <iostream>
using std::vector;
class Matrix
{
private:
	std::vector<double> vv;
	int row;
	int col;
public:
	Matrix()
	{
		vv = vector<double>();
	}
	Matrix(int row, int col)
	{
		this->row = row;
		this->col = col;
		vv = vector<double>(row*col);
	}
	Matrix(int row, int col, double val) : Matrix(row, col)
	{
		for (int i = 0; i < row*col; i++)
			vv[i] = val;
	}

	int gRow() const
	{
		return row;
	}
	int gCol() const
	{
		return col;
	}
	double* operator [] (int i)
	{
		return &vv[i*col];
	}
	Matrix operator * (Matrix& m)
	{
		if (gCol() != m.gRow()) return Matrix();
		Matrix newMatr(gRow(), m.gCol());
		for (int z = 0; z < gRow(); z++)
			for (int i = 0; i < m.gCol(); i++)
				for (int j = 0; j < m.gRow(); j++)
					newMatr[z][i] += (*this)[z][j] * m[j][i];
		return newMatr;
	}
	friend std::ostream& operator<<(std::ostream& os, Matrix& m)
	{
		if (m.gRow() == 0) os << 0;
		for (int i = 0; i < m.gRow(); i++)
		{
			for (int j = 0; j < m.gCol(); j++)
				os << m[i][j] << ' ';
			os << '\n';
		}
		os << '\n';
		return os;
	}
};