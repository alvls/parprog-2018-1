#pragma once
#include <vector>
using std::vector;
typedef double Element;

struct Matrix
{
private:
    std::vector<Element> vv;
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
        vv = vector<Element>(row*col);
    }
    Matrix(int row, int col, Element val) : Matrix(row, col)
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
    Element* operator [] (int i)
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
struct MatrixCCS
{
    vector<Element> values;
    vector<int> rows;
    vector<int> pointer;
    int N;
    MatrixCCS() {}
    MatrixCCS(Matrix &M, int notZero, int n) :N(n)
    {
        values = vector<Element>(notZero);
        rows = vector<int>(N);
        pointer = vector<int>(N + 1);

        vector<int> task;
        for (int j = 0; j < N; j++)
        {
            bool isNotZero = false;
            for (int i = 0; i < N; i++)
            {
                Element el = M[j][i];
                if (el != 0.0)
                {
                    if (isNotZero == false)
                    {
                        isNotZero = true;
                        pointer[j] = pointer.size();
                    }
                    rows.push_back(i);
                    values.push_back(el);
                }
            }
            if (isNotZero == false)
            {
                task.push_back(j);
            }
        }
        pointer[N] = pointer.size() + 1;
        for (int i = task.size() - 1; i--; i >= 0)
            pointer[task[i]] = pointer[task[i] + 1];
    }
    Matrix convertToMatrix()
    {
        Matrix A(N, N, 0.0);
        for (int i = 0; i < N; i++)
        {
            int numElementsInCol = pointer[i + 1] - pointer[i];
            if (numElementsInCol == 0) continue;
            for (int pos = pointer[i]; pos < pointer[i + 1]; pos++)
            {
                Element el = values[pos];
                A[i][rows[pos]] = el;
            }
        }
    }
};