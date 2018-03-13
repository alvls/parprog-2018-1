#include <omp.h>
#include <vector>
#define index(col, row, n) (col*n+row)
typedef double Element;

using namespace std;
struct MatrixCCS
{
    vector<Element> values;
    vector<int> rows;
    vector<int> pointer;
    int N;
    MatrixCCS(Element *M, int n):N(n)
    {
        vector<int> task;
        for (int j = 0; j < N; j++)
        {
            bool isNotZero = false;
            for (int i = 0; i < N; i++)
            {
                Element el = M[index(j, i, N)];
                if (el != 0.0)
                {
                    if (isNotZero == false)
                    {
                        isNotZero = true;
                        pointer[j] = values.size();
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
        pointer[N] = values.size()+1;
        for (int i = task.size() - 1; i--; i >= 0)
            pointer[task[i]] = pointer[task[i] + 1];
    }
    Element * convertToMatrix()
    {
        Element *A = new Element[N*N];
        for (int i = 0; i < N*N; i++) A[i] = 0.0;
        for (int i = 0; i < N; i++)
        {
            int numElementsInCol = pointer[i + 1] - pointer[i];
            if (numElementsInCol == 0) continue; 
            for (int pos = pointer[i]; pos < pointer[i + 1]; pos++)
            {
                Element el = values[pos];
                A[index(i, rows[pos], N)] = el;
            }
        }
    }
};
void MatrMatrMult(double * A, double * B, double * C, int N)
{
	int i, j, k;
#pragma omp parallel for private(j, k)
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			C[i * N + j] = 0.0;
			for (k = 0; k < N; k++)
				C[i * N + j] += A[i * N + k] * B[k * N + j];
		}
	}
}

void MatrMult(MatrixCCS &A, MatrixCCS &B, MatrixCCS &Res)
{

}