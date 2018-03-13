#include <omp.h>
#include <vector>

typedef double Element;
#define index(col, row, n) (col*n+row)
#define push(arr, size, element) arr[size++] = element
#define ConstMatrix(values, rows, pointer) const vector<Element> &values, const vector<int> &rows, const vector<int> &pointer
#define Matrix(values, rows, pointer) vector<Element> &values, vector<int> &rows, vector<int> &pointer

using std::vector;
struct MatrixCCS
{
    vector<Element> values;
    vector<int> rows;
    vector<int> pointer;
    int N;
    MatrixCCS() {}
    MatrixCCS(Element *M, int notZero, int n):N(n)
    {
        values = vector<Element>(notZero);
        rows = vector<int> (N);
        pointer = vector<int>(N + 1);

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
        pointer[N] = pointer.size()+1;
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

void MatrMatrMult(Element *a, Element *b, Element *res, int N)
{
    MatrixCCS A(a, N*N, N), B(b, N*N, N), Res(res, N*N, N);
}
void MatrMatrMult(ConstMatrix(values_A, rows_A, pointer_A), ConstMatrix(values_B, rows_B, pointer_B), Matrix(values_res, rows_res, pointer_res))
{

}

/*void MatrMatrMult(double * A, double * B, double * C, int N)
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
}*/