#ifndef CRSMATRIX_H
#define CRSMATRIX_H

#include <vector>
#include <iterator>

using std::vector;

const double INF = 0.000001;

class CRSmatrix {
public:
	CRSmatrix() : Size(0), NotZero(0) {}
	CRSmatrix(int size, int nzelem, vector<double> value, vector<int> col, vector<int> sparseRow) : 
		Size(size), NotZero(nzelem), Value(value), Col(col), SparseRow(sparseRow) {}

	CRSmatrix(int size, int nzelem, double * value, int * col, int * sparseRow) : Size(size), NotZero(nzelem)
	{
		Value.assign(value, value + nzelem);
		delete[] value;
		Col.assign(col, col + nzelem);
		delete[] col;
		SparseRow.assign(sparseRow, sparseRow + size + 1);
		delete[] sparseRow;
	}

	int getSize()
	{
		return Size;
	}

	int getNotZero()
	{
		return NotZero;
	}

	double* getValue()
	{
		double* tmp = new double[NotZero];
		std::copy(Value.begin(), Value.end(), stdext::checked_array_iterator<double*>(tmp, Value.size()));
		return tmp;
	}

	int* getCol()
	{
		int* tmp = new int[NotZero];
		std::copy(Col.begin(), Col.end(), stdext::checked_array_iterator<int*>(tmp, Col.size()));
		return tmp;
	}

	int* getSparseRow()
	{
		int* tmp = new int[Size + 1];
		std::copy(SparseRow.begin(), SparseRow.end(), stdext::checked_array_iterator<int*>(tmp, Size + 1));
		return tmp;
	}

	CRSmatrix getTransposed() const
	{
		CRSmatrix tmpMatrix;

		vector<vector<int>> v1(this->Size);
		vector<vector<double>> v2(this->Size);

		int position = 0;
		for (int i = 0; i < Size; ++i)
		{
			while (position != NotZero && position < SparseRow[i + 1])
			{
				v1[Col[position]].emplace_back(i);
				v2[Col[position]].emplace_back(Value[position]);
				++position;
			}
		}

		tmpMatrix.Size = Size;
		tmpMatrix.NotZero = NotZero;

		tmpMatrix.Value.reserve(NotZero);
		tmpMatrix.Col.reserve(NotZero);
		tmpMatrix.SparseRow.resize(Size + 1);

		tmpMatrix.SparseRow[0] = 0;

		for (int i = 1; i <= Size; ++i)
			tmpMatrix.SparseRow[i] = tmpMatrix.SparseRow[i - 1] + v1[i - 1].size();

		for (int i = 0; i < Size; ++i)
		{
			tmpMatrix.Col.insert(tmpMatrix.Col.end(), v1[i].begin(), v1[i].end());
			tmpMatrix.Value.insert(tmpMatrix.Value.end(), v2[i].begin(), v2[i].end());
		}

		return tmpMatrix;
	}

	CRSmatrix operator*(const CRSmatrix & crsmatrix)
	{
		CRSmatrix tmp = crsmatrix.getTransposed();
		CRSmatrix tmpMatrix;
		tmpMatrix.Size = Size;
		tmpMatrix.SparseRow.resize(Size + 1);


		int lastSize = 0;

		for (int i = 0; i < Size; ++i)
		{
			vector<int> tmp_col(Size, -1);

			for (int j = SparseRow[i]; j < SparseRow[i + 1]; ++j)
				tmp_col[Col[j]] = j;

			for (int j = 0; j < Size; ++j)
			{
				double sum = 0;

				for (int k = tmp.SparseRow[j]; k < tmp.SparseRow[j + 1]; ++k)
				{
					int col = tmp_col[tmp.Col[k]];
					if (col != -1)
						sum += Value[col] * tmp.Value[k];
				}

				if (abs(sum) > INF)
				{
					tmpMatrix.Value.push_back(sum);
					tmpMatrix.Col.push_back(j);
				}

			}
			tmpMatrix.SparseRow[i] = lastSize;
			lastSize = tmpMatrix.Value.size();
		}

		tmpMatrix.SparseRow[Size] = tmpMatrix.Col.size();

		tmpMatrix.NotZero = tmpMatrix.Col.size();

		return tmpMatrix;
	}
private:
	int Size;
	int NotZero;
	vector<double> Value;
	vector<int> Col;
	vector<int> SparseRow;
};
#endif // !CRSMATRIX_H