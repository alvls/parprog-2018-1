#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
#include <omp.h>

#include <string>
#include <fstream>

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

        omp_set_num_threads(omp_get_max_threads());
        #pragma omp parallel for
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
        if (res == false) 
            return false;

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
struct Task
{
    int pointerStart;
    int pointerEnd;
    int taskIndex;
    Task():pointerStart(0), pointerEnd(0), taskIndex(0) {}
    Task(int a, int b, int c) :pointerStart(a), pointerEnd(b), taskIndex(c) {}
};
struct PrepareData
{
	PrepareData(int numThread, int N)
	{
		numTask = 4 * numThread;
		if (numTask > N)
			numTask = N;
	}
    int numTask;
    vector<Task> task;
    vector<int> elCountM;

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
	void setValues(vector<Element> Valuse)
	{
		values = Valuse;
	}
	void setRows(vector<int> Rows)
	{
		rows = Rows;
	}
	void setPointer(vector<int> Pointer)
	{
		pointer = Pointer;
	}
    void convertToMatrix(Matrix &A)
    {
        for (int i = 0; i < pointer.size()-1; i++)
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
        for (int i = 0; i < m.values.size();i++)
        {
            values.push_back(m.values[i]);
            rows.push_back(m.rows[i]);
        }
        for (int i = 1; i < m.pointer.size(); i++)
        {
            int start = pointer[pointer.size()-1];
            pointer.push_back(m.pointer[i] - m.pointer[i-1] + start);
        }
    }
    MatrixCCS operator * (const MatrixCCS &m)
    {
        MatrixCCS res(N);
		transpositionMatrix();
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
		transpositionMatrix();
        return res;
    }
	
	static void prepareTask(PrepareData &data, vector<MatrixCCS> &tmp, const MatrixCCS &m, int N)
	{
		tmp = vector<MatrixCCS>(data.numTask, MatrixCCS(N));
		data.elCountM = vector<int>(data.numTask);

		data.task = vector<Task>(data.numTask);
		//prepare task
		int sizeTask = m.N / data.numTask + (bool)(m.N % data.numTask);
		for (int i = 0; i < data.numTask; i++)
			data.task[i] = Task(i*sizeTask, std::min((i + 1)*sizeTask, m.N), i % data.numTask);
		int lastPointerM = 0;
		for (int i = 0; i < data.numTask; i++)
		{
			data.elCountM[i] = lastPointerM;
			int jstart = data.task[i].pointerStart;
			const int jend = data.task[i].pointerEnd;
			for (jstart; jstart < jend; jstart++)
			{
				lastPointerM += m.pointer[jstart + 1] - m.pointer[jstart];
			}
		}
	}
	//need prepareTask(data, tmp, m);
    void quickParallelMult(const MatrixCCS &m, PrepareData &data, vector<MatrixCCS> &tmp)
    {
		vector<int> *cols = &rows;
#pragma omp parallel for schedule(static)
        for (int itask = 0; itask < data.task.size(); itask++)
        {
            for (int j = data.task[itask].pointerStart; j < data.task[itask].pointerEnd; j++)
            {
                int indexTask = data.task[itask].taskIndex;
                int numElInResCol = 0;
                const int numElementInCol = m.pointer[j + 1] - m.pointer[j];
                if (numElementInCol == 0)
                {
                    int size = tmp[indexTask].pointer.size();
                    tmp[indexTask].pointer.push_back(tmp[indexTask].pointer[size - 1]);
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
                    int tmpElCountM = data.elCountM[indexTask];
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
                        tmp[indexTask].values.push_back(sum);
                        tmp[indexTask].rows.push_back(i);
                        numElInResCol++;
                    }
                }
                const int size = tmp[indexTask].pointer.size();
                tmp[indexTask].pointer.push_back(tmp[indexTask].pointer[size - 1] + numElInResCol);
                data.elCountM[indexTask] += numElementInCol;
            }
        }
    }
	static void uniteMatrixs(vector<MatrixCCS> &tmp)
	{
		for (int i = 1; i < tmp.size(); i++)
		{
			tmp[0].unite(tmp[i]);
		}
		if (tmp[0].pointer.size() < tmp[0].N + 1)
			tmp[0].pointer.push_back(tmp[0].values.size());
	}

    MatrixCCS parallelMult(const MatrixCCS &m, const int numThreads)
    {
        int numTask = numThreads;
        if (numTask > N)
            numTask = N;
        vector<MatrixCCS> tmp(numTask, MatrixCCS(N));
		vector<int> elCountM(numTask);
		vector<int> *cols = &rows;              

		vector<Task> task(numTask);
		{
            //prepare task
			int sizeTask = m.N / numTask + (bool)(m.N % numTask);
            for (int i = 0; i < numTask; i++)
                task[i] = Task(i*sizeTask, std::min((i + 1)*sizeTask, m.N), i % numTask);
			int lastPointerM = 0;
			for (int i = 0; i < numTask; i++)
			{
				elCountM[i] = lastPointerM;
				int jstart = task[i].pointerStart;
				const int jend = task[i].pointerEnd;
				for (jstart; jstart < jend; jstart++)
				{
					lastPointerM += m.pointer[jstart + 1] - m.pointer[jstart];
				}
			}
		}

        #pragma omp parallel for
        for (int itask = 0; itask < task.size(); itask++)
        {
            for (int j = task[itask].pointerStart; j < task[itask].pointerEnd; j++)
            {
                int indexTask = task[itask].taskIndex;
                int numElInResCol = 0;
                const int numElementInCol = m.pointer[j + 1] - m.pointer[j];
                if (numElementInCol == 0)
                {
                    int size = tmp[indexTask].pointer.size();
                    tmp[indexTask].pointer.push_back(tmp[indexTask].pointer[size - 1]);
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
                    int tmpElCountM = elCountM[indexTask];
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
                        tmp[indexTask].values.push_back(sum);
                        tmp[indexTask].rows.push_back(i);
                        numElInResCol++;
                    }
                }
                const int size = tmp[indexTask].pointer.size();
                tmp[indexTask].pointer.push_back(tmp[indexTask].pointer[size - 1] + numElInResCol);
                elCountM[indexTask] += numElementInCol;
            }
        }
		for (int i = 1; i < tmp.size(); i++)
		{
			tmp[0].unite(tmp[i]);
		}
		if (tmp[0].pointer.size() < N + 1)
			tmp[0].pointer.push_back(tmp[0].values.size());
		return tmp[0];
    }
	MatrixCCS testMult(const MatrixCCS &m, int numThreads = 2)
	{
		transpositionMatrix();

		vector<MatrixCCS> tmp(numThreads, MatrixCCS(N));

		vector<int> *cols = &rows;
		vector<int> elCountM(numThreads);
		int size = m.N / numThreads + (bool)(m.N % numThreads);
		vector<pair<int,int>> j_index(numThreads);
		for (int i = 0; i < numThreads; i++)
		{
			j_index[i] = std::make_pair(i*size, std::min((i+1)*size, m.N));
		}
		int last_pointerM = 0;
		for (int i = 0; i < numThreads; i++)
		{
			elCountM[i] = last_pointerM;
			int jstart = j_index[i].first;
			int jend = j_index[i].second;
			for (jstart; jstart < jend; jstart++)
			{
				last_pointerM += m.pointer[jstart + 1] - m.pointer[jstart];
			}
		}
		for (int indexThread = 0; indexThread < numThreads; indexThread++)
			for (int j = j_index[indexThread].first; j < j_index[indexThread].second; j++)
			{
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
					int tmpElCountM = elCountM[indexThread];
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
				elCountM[indexThread] += numElementInCol;
			}
        
		for (int i = 1; i < numThreads; i++)
        {
            tmp[0].unite(tmp[i]);
        }
       if (tmp[0].pointer.size() < N + 1)
            tmp[0].pointer.push_back(tmp[0].values.size());
       
		transpositionMatrix();
		return tmp[0];
	}

    bool operator == (const MatrixCCS &m)
    {
        return (N == m.N & values == m.values & rows == m.rows & pointer == m.pointer);
    }
};
