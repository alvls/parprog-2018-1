#pragma once
#include <vector>
#include <iostream>
using std::ostream;
using std::vector;
typedef double Element;

class Matrix
{
private:
    int row = 0;
    int col = 0;
public:
    std::vector<Element> vv;
    Matrix()
    {
        vv = vector<double>();
    }
    Matrix(int col, int row)
    {
        this->row = row;
        this->col = col;
        vv = vector<Element>(row*col);
    }
    Matrix(int col, int row, Element val)
    {
        this->row = row;
        this->col = col;
        vv = vector<Element>(row*col, val);
    }

    int gRow() const
    {
        return row;
    }
    int gCol() const
    {
        return col;
    }
    int gSize() const
    {
        return row*col;
    }
    Element *getP()
    {
        return &vv[0];
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
    void transpositionMatrix()
    {
        Matrix A(row, col);
        for (int i = 0; i < col; i++)
            for (int j = 0; j < row; j++)
            {
                A[i][j] = (*this)[j][i];
            }
        std::swap(row, col);
        vv = A.vv;
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
class MatrixCCS
{
private:
    vector<Element> values;
    vector<int> rows;
    vector<int> pointer;
    int N;
public:
    MatrixCCS() {}
    MatrixCCS(Matrix &M) :N(M.gRow())
    {
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
                        pointer[j] = (int)values.size();
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
        pointer[N] = (int)values.size();
        for (int i = (int)task.size() - 1; i >= 0; i--)
            pointer[task[i]] = pointer[task[i] + 1];
    }
    void convertToMatrix(Matrix &A)
    {
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