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
    Element* operator [] (int j)
    {
        return &vv[j*col];
    }
    Matrix operator * (Matrix& m)
    {
        if (gCol() != m.gRow()) return Matrix();
        Matrix newMatr(gRow(), m.gCol());
        for (int j = 0; j < m.gRow(); j++)
            for (int i = 0; i < gCol(); i++)
                for (int z = 0; z < gCol(); z++)
                    newMatr[j][i] += (*this)[z][i] * m[j][z];
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
                os << m[j][i] << ' ';
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
    MatrixCCS(int n) :N(n) 
    {
        pointer.push_back(0);
    }
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
    void unite(const MatrixCCS &m)
    {
        int numCol = pointer.size();
        int start = pointer[numCol - 1];
        for (int i = 0; i < m.values.size();i++)
        {
            values.push_back(m.values[i]);
            rows.push_back(m.rows[i]);
        }
        for (int i = 0; i < m.pointer.size() - 1; i++)
        {
            pointer.push_back(m.pointer[i] + start);
        }
    }
    MatrixCCS operator * (const MatrixCCS &m)
    {
        MatrixCCS res(N);
        res.pointer.push_back(0);        
        vector<int> *cols = &rows;
        int elCountM = 0;
        for (int j = 0; j < m.N; j++)
        {            
            int numElInResCol = 0;
            const int numElementInCol = m.pointer[j + 1] - m.pointer[j];
            if (numElementInCol == 0)
            {
                int size = res.pointer.size();
                res.pointer.push_back(res.pointer[size - 1]);
                continue;
            }
            int elCountThis = 0;
            for (int i = 0; i < N; i++)
            {                   
                const int numElementInRow = pointer[i + 1] - pointer[i];
                if (numElementInRow == 0)
                {                 
                    continue;
                }               
                int tmpNumElCol = numElementInCol;
                int tmpNumElRow = numElementInRow;

                Element sum = 0;
                int tmpElCountM = elCountM;               
                for (int z = 0; z < std::min(tmpNumElCol, tmpNumElRow);)
                {                  
                    int colThis = (*cols)[elCountThis];
                    int rowM = m.rows[tmpElCountM];
                    if (colThis == rowM)
                    {
                        sum += values[elCountThis] * m.values[tmpElCountM];
                        tmpNumElCol--;
                        tmpNumElRow--;
                        tmpElCountM++;
                        elCountThis++;                     
                    }
                    else if (colThis < rowM)
                    {
                        tmpNumElRow--;
                        elCountThis++;
                    }
                    else
                    {
                        tmpNumElCol--;
                        tmpElCountM++;
                    }                    
                }  
                for (int z = 0; z < tmpNumElRow; z++)
                    elCountThis++;

                if (sum != 0)
                {
                    res.values.push_back(sum);
                    res.rows.push_back(i);
                    numElInResCol++;
                }               
            }
            const int size = res.pointer.size();
            res.pointer.push_back(res.pointer[size - 1] + numElInResCol);
            elCountM += numElementInCol;
        }     
        return res;
    }
    MatrixCCS parallelMult(const MatrixCCS &m)
    {
        //matrix must be transposition          
        int numThreads = omp_get_num_threads();
        vector<MatrixCCS> tmp(numThreads, MatrixCCS(N));

        vector<int> *cols = &rows;
        int elCountM = 0;
        for (int j = 0; j < m.N; j++)
        {
            int indexThread = omp_get_thread_num();
            int numElInResCol = 0;
            const int numElementInCol = m.pointer[j + 1] - m.pointer[j];
            if (numElementInCol == 0)
            {
                int size = tmp[indexThread].pointer.size();
                tmp[indexThread].pointer.push_back(tmp[indexThread].pointer[size - 1]);
                continue;
            }
            int elCountThis = 0;
            for (int i = 0; i < N; i++)
            {
                const int numElementInRow = pointer[i + 1] - pointer[i];
                if (numElementInRow == 0)
                {
                    continue;
                }
                int tmpNumElCol = numElementInCol;
                int tmpNumElRow = numElementInRow;

                Element sum = 0;
                int tmpElCountM = elCountM;
                for (int z = 0; z < std::min(tmpNumElCol, tmpNumElRow);)
                {
                    int colThis = (*cols)[elCountThis];
                    int rowM = m.rows[tmpElCountM];
                    if (colThis == rowM)
                    {
                        sum += values[elCountThis] * m.values[tmpElCountM];
                        tmpNumElCol--;
                        tmpNumElRow--;
                        tmpElCountM++;
                        elCountThis++;
                    }
                    else if (colThis < rowM)
                    {
                        tmpNumElRow--;
                        elCountThis++;
                    }
                    else
                    {
                        tmpNumElCol--;
                        tmpElCountM++;
                    }
                }
                for (int z = 0; z < tmpNumElRow; z++)
                    elCountThis++;

                if (sum != 0)
                {
                    tmp[indexThread].values.push_back(sum);
                    tmp[indexThread].rows.push_back(i);
                    numElInResCol++;
                }
            }
            const int size = tmp[indexThread].pointer.size();
            tmp[indexThread].pointer.push_back(tmp[indexThread].pointer[size - 1] + numElInResCol);
            elCountM += numElementInCol;
        }
        for (int i = 1; i < numThreads; i++)
        {
            tmp[0].unite(tmp[i]);
        }
        tmp[0].pointer.push_back(tmp[0].values.size());
        return tmp[0];
    }
};
