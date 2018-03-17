#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
using std::ostream;
using std::vector;
using std::list;
using std::pair;
using std::make_pair;
typedef double Element;

class Matrix
{
protected:
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

    bool operator == (const Matrix &m)
    {
        bool res = (row == m.row & col == m.col);
        if (res == false) return false;
        for (int i = 0; i < vv.size(); i++)
            if (vv[i] != m.vv[i]) return false;
        return true;
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
protected:
    vector<Element> values;
    vector<int> rows;
    vector<int> pointer;
    int N;
public:
    MatrixCCS() {}
    MatrixCCS(Matrix &M) :N(M.gRow())
    {
        pointer = vector<int>(N + 1);
        int lastCount = 0;
        for (int j = 0; j < N; j++)
        {
            int curCount = 0;
            for (int i = 0; i < N; i++)
            {       
                Element el = M[j][i];
                if (el != 0.0)
                {
                    curCount++;
                    rows.push_back(i);
                    values.push_back(el);
                }
            }
            if (j != 0)
            {
                pointer[j] = pointer[j-1] + lastCount;
            }
            lastCount = curCount;
        }
        pointer[N] = (int)values.size();
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
    void transpositionMatrix()
    {
        vector<vector<pair<Element, int>>> tmp(N, vector<pair<Element, int>>());
        int pCount = 0;
        int numElementsInCol = 0;
        for (int i = 0; i < values.size(); i+= numElementsInCol)
        {   
            numElementsInCol = pointer[pCount + 1] - pointer[pCount];
            for (int z = i; z < i + numElementsInCol; z++)
            {
                int row = rows[z];
                int col = pCount;
                Element el = values[z];
                tmp[row].push_back(make_pair(el, col));
            }
            pCount++;
        }
        pCount = 0;
        vector<int> *cols = &rows;
        int lastCount = 0;
        int vCount = 0;
        for (int i = 0; i < N; i++)
        {
            int numElementInCol = (int)tmp[i].size();
            if (numElementInCol > 0)
            {
                for (int j = 0; j < numElementInCol; j++)
                {
                    values[vCount] = tmp[i][j].first;
                    (*cols)[vCount] = tmp[i][j].second;
                    vCount++;
                }
            }
            if (pCount != 0)
            {
                pointer[pCount] = pointer[pCount - 1] + lastCount;
            }
            lastCount = numElementInCol;
            pCount++;

        }
    }
    MatrixCCS operator * (const MatrixCCS &m)
    {
        MatrixCCS res;
        transpositionMatrix();
        vector<int> *cols = &rows;

        for (int j = 0; j < m.N; j++)
        {
            int pCountM = 0;
            int elCountThis = 0;
            int elCountM = 0;
            const int numElementInCol = m.pointer[pCountM + 1] - m.pointer[pCountM];
            if (numElementInCol == 0)
            {
                pCountM++;
                continue;
            }
            for (int i = 0; i < N; j++)
            {   
                int pCountThis = 0;
                const int numElementInRow = pointer[pCountThis + 1] - pointer[pCountThis];
                if (numElementInRow == 0) 
                    continue;
                int tmpNumElCol = numElementInCol;
                int tmpNumElRow = numElementInRow;

                Element sum = 0;
                int tmpElCountM = elCountM;
                for (int z = 0; z < std::min(tmpNumElCol, tmpNumElRow);)
                {                  
                    const int colThis = (*cols)[tmpElCountM];
                    const int rowM = m.rows[elCountM];
                    if (colThis == rowM)
                    {
                        sum += values[tmpElCountM] * m.values[elCountM];
                        tmpNumElCol--;
                        tmpNumElRow--;
                        tmpElCountM++;
                        elCountM++;
                    }
                    else if (colThis < rowM)
                    {
                        tmpNumElCol--;
                        tmpElCountM++;
                    }
                    else
                    {
                        tmpNumElRow--;
                        elCountM++;
                    }                    
                }     
                if (sum != 0)
                {
                    res.values.push_back(sum);
                    res.rows.push_back(i);
                }

            }
            elCountThis += numElementInCol;
            pCountM++;
        }
        transpositionMatrix();
        return res;
    }
};