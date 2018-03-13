#include <omp.h>
#include <string>
#include<iostream>
#include <vector>

typedef double Element;
#define index(col, row, n) (col*n+row)
#define ConstMatrix(values, rows, pointer) const vector<Element> &values, const vector<int> &rows, const vector<int> &pointer
#define Matrix(values, rows, pointer) vector<Element> &values, vector<int> &rows, vector<int> &pointer

using std::vector;
using std::string;
struct Matr
{
    Element *M;
    int N;

    vector<Element> values;
    vector<int> rows;
    vector<int> pointer;
    Matr(int n): N(n) {}
    void MatrToMatrCCS()
    {
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
        pointer[N] = pointer.size() + 1;
        for (int i = task.size() - 1; i--; i >= 0)
            pointer[task[i]] = pointer[task[i] + 1];
        delete[]M;
    }
    void MatrCSStoMatr()
    {
        M = new Element[N*N];
        for (int i = 0; i < N*N; i++) M[i] = 0.0;
        for (int i = 0; i < N; i++)
        {
            int numElementsInCol = pointer[i + 1] - pointer[i];
            if (numElementsInCol == 0) continue;
            for (int pos = pointer[i]; pos < pointer[i + 1]; pos++)
            {
                Element el = values[pos];
                M[index(i, rows[pos], N)] = el;
            }
        }
    }
};
void MatrMatrMult(Element *A, Element *B, Element *Res, int N);
void MatrMatrMult(ConstMatrix(values_A, rows_A, pointer_A), ConstMatrix(values_B, rows_B, pointer_B), Matrix(values_res, rows_res, pointer_res));

int main(int argc, char * argv[])//читает из бинарного файла, запускает программу, пишет в бинарный файл
{
	int num_threads = 1;
	string name = "matr";
	string number = "";
	string extensionIn = ".in";
	string extensionOut = ".out";
	if (argc > 1)
	{
		num_threads = atoi(argv[1]);
		if (argc > 2)
		{
			number = argv[2];
		}
	}

	int N;
    Matr A(N), B(N), C(N);

	freopen((name + number + extensionIn).c_str(), "rb", stdin);
	freopen((name + number + extensionOut).c_str(), "wb", stdout);
	fread(&N, sizeof(N), 1, stdin);
	A.M = new Element[N * N];
	B.M = new Element[N * N];
	C.M = new Element[N * N];
	fread(A.M, sizeof(*A.M), N * N, stdin);
	fread(B.M, sizeof(*B.M), N * N, stdin);
    A.MatrToMatrCCS();
    B.MatrToMatrCCS();
    
    omp_set_num_threads(num_threads);
	double time = omp_get_wtime();
    A.MatrCSStoMatr();
	//MatrMatrMult(A.values, A.rows, A.pointer, B.values, B.rows, B.pointer, C.values, C.rows, C.pointer);
	time = omp_get_wtime() - time;

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(A.M, sizeof(*A.M), N * N, stdout);

	return 0;
}