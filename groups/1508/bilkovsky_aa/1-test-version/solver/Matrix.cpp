#include <ccomplex>
#include <vector>
using namespace std;
class Matrix
{
	private:
		int _size;
		int _notNull;
		vector<int>  _secondIndex, _position;
		vector<complex<int>> _elements;
	public:
		Matrix() : _size(0), _notNull(0) { }
		Matrix(int size, int count, complex<int>* elements,int* lj,int* li) {
			_size = size;
			_notNull = count;
			_elements.assign(elements,elements + count);
			_secondIndex.assign(lj,lj + count);
			_position.assign(li,li + size + 1);
		}
		void InitializeMatrix(int size,int notNull,Matrix &M) {
			M._size = size;
			M._notNull = notNull;
			M._elements.reserve[notNull];
			M._secondIndex.reserve[notNull];
			M._position.reserve[notNull + 1];
		}
		complex<int> operator ()(int i, int j) {
			complex<int> result = complex<int>(0,0); 
			int n1 = _position[i]; 
			int n2 = _position[i + 1];
			for (int iter = n1; iter < n2; iter++)
			{
				if (_secondIndex[iter] == j)
				{
					result = _elements[iter];
					break;
				}
			}
			return result;
		}
		Matrix operator *(const Matrix &M){
			Matrix tmp = Matrix(M);
			return tmp;
		}
		Matrix GetTransposed(const Matrix &M) 
		{
			Matrix temp;

			vector<vector<int>> v1(_size);
			vector<vector<complex<int>>> v2(_size);

			int pos = 0;
			for (int i = 0; i < M._size; ++i)
			{
				while (pos != _notNull && pos < M._position[i + 1])
				{
					v1[M._secondIndex[pos]].emplace_back(i);
					v2[M._secondIndex[pos]].emplace_back(M._elements[pos]);
					++pos;
				}
			}

			temp._size = M._size;
			temp._notNull = M._notNull;

			temp._elements.reserve[M._notNull];
			temp._secondIndex.reserve[M._notNull];
			temp._position.reserve[M._size + 1];

			temp._position[0] = 0;

			for (int i = 1; i <= M._size; ++i)
				temp._position[i] = temp._position[i - 1] + v1[i - 1].size();

			for (int i = 0; i < M._size; ++i)
			{
				temp._secondIndex.insert(temp._secondIndex.end(), v1[i].begin(), v1[i].end());
				temp._elements.insert(temp._elements.end(), v2[i].begin(), v2[i].end());
			}

			return temp;
		}

		Matrix operator*(const Matrix &M )
		{
			Matrix tmp = crsmatrix.getTransposed(this);
			Matrix tmpMatrix;
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
};