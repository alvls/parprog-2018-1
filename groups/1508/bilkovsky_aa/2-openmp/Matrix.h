#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#include <ccomplex>
#include <vector>
#include<ctime>
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
    Matrix(int size, int count, complex<int>* elements, int* lj, int* li) {
        _size = size;
        _notNull = count;
        _elements.assign(elements, elements + count);
        _secondIndex.assign(lj, lj + count);
        _position.assign(li, li + size + 1);
    }
    void InitializeMatrix(int size, int notNull, Matrix &M) {
        M._size = size;
        M._notNull = notNull;
        M._elements.reserve(notNull);
        M._secondIndex.reserve(notNull);
        M._position.reserve(notNull + 1);
    }
    complex<int> operator ()(int i, int j) const {
        complex<int> result = complex<int>(0, 0);
        int n1 = _position[i];
        int n2 = _position[i + 1];
        for (int iter = n1; iter < n2; iter++)
        {
            if (_secondIndex[iter - 1] == j)
            {
                result = _elements[iter - 1];
                break;
            }
        }
        return result;
    }
    Matrix GetTransposed() const
    {
        Matrix temp;

        vector<vector<int>> v1(_size);
        vector<vector<complex<int>>> v2(_size);

        int pos = 0;
        for (int i = 0; i < _size; ++i)
        {
            while (pos != _notNull && pos < _position[i + 1])
            {
                v1[_secondIndex[pos]].emplace_back(i);
                v2[_secondIndex[pos]].emplace_back(_elements[pos]);
                ++pos;
            }
        }

        temp._size = _size;
        temp._notNull = _notNull;

        temp._elements.reserve(_notNull);
        temp._secondIndex.reserve(_notNull);
        temp._position.resize(_size + 1);

        temp._position[0] = 0;


        for (int i = 0; i < _size; ++i)
        {
            temp._secondIndex.insert(temp._secondIndex.end(), v1[i].begin(), v1[i].end());
            temp._elements.insert(temp._elements.end(), v2[i].begin(), v2[i].end());
            temp._position[i + 1] = temp._position[i] + v1[i].size();
        }

        return temp;
    }

    Matrix operator*(const Matrix &M)
    {
        Matrix temp = M.GetTransposed();
        Matrix result;
        result._size = _size;
        result._position.resize(_size + 1);


        int pos = 0;
#pragma omp parallel
        {
        #pragma omp for
        for (int i = 0; i < _size; ++i)
        {
            vector<int> secondIndexestmp(_size, -1);

            for (int j = _position[i]; j < _position[i + 1]; ++j)
                secondIndexestmp[_secondIndex[j]] = j;

            for (int j = 0; j < _size; ++j)
            {
                complex<int> value = 0;

                for (int k = temp._position[j]; k < temp._position[j + 1]; ++k)
                {
                    int index = secondIndexestmp[temp._secondIndex[k]];
                    if (index != -1)
                        value += _elements[index] * temp._elements[k];
                }
                if (value.real() != 0 || value.imag() != 0)
                {
                    result._elements.push_back(value);
                    result._secondIndex.push_back(j);
                }

            }
            result._position[i] = pos;
            pos = result._elements.size();
        }
    }
        result._position[_size] = result._secondIndex.size();

        result._notNull = result._secondIndex.size();

        return result;
    }
    void WriteMatrix(char* path, double time = 0)
    {
        freopen(path, "wb", stdout);
        fwrite(&time, sizeof(time), 1, stdout);
        fwrite(&_size, sizeof(_size), 1, stdout);
        fwrite(&_notNull, sizeof(_notNull), 1, stdout);
        complex<int> *elements = new complex<int>[_notNull];
        copy(_elements.begin(), _elements.end(), elements);
        int *secondIndex = new int[_notNull];
        int *position = new int[_size + 1];
        copy(_secondIndex.begin(), _secondIndex.end(), secondIndex);
        copy(_position.begin(), _position.end(), position);
        fwrite(elements, sizeof(*elements), _notNull, stdout);
        fwrite(secondIndex, sizeof(*secondIndex), _notNull, stdout);
        fwrite(position, sizeof(*position), _size + 1, stdout);
    }
};