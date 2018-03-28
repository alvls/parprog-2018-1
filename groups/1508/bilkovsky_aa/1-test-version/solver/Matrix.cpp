#include <ccomplex>
using namespace std;
class Matrix
{
	private:
		int _size;
		int _notNull;
		int  *_secondIndex, *_place;
		complex<int> *_elements;
	public:
		Matrix() : _size(0), _notNull(0) { }
		Matrix(int size, int count, complex<int>* elements,int* lj,int* li) {
			_size = size;
			_notNull = count;
			_elements = elements;
			_secondIndex = lj;
			_place = li;
		}
		Matrix(const Matrix &M) {
			_size = M._size;
			_notNull = M._notNull;
			_elements = M._elements;
			_secondIndex = M._secondIndex;
			_place = M._place;
		}
		complex<int> operator ()(int i, int j) {
			complex<int> result = complex<int>(0,0); 
			int n1 = _place[i]; 
			int n2 = _place[i + 1];
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
};