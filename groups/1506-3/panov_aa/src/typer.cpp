#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::swap;

typedef double Element;

inline Element& index(int i, int j, int N, Element *M)
{
    return M[i*N + j];
}
void TranspositionMatrixBtoA(Element *A, Element *B, int N)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            index(i, j, N, A) = index(j, i, N, B);
        }
}
void readMatrix(Element *A, int N)
{
    Element *B = new Element[N*N];
	for (int i = 0; i < N*N; i++)
	{
		cin >> B[i];
	}
    TranspositionMatrixBtoA(A, B, N);
    delete[]B;
}
void writeMatrixBin(double *A, int N)
{
    fwrite(&N, sizeof(N), 1, stdout);
	fwrite(A, sizeof(*A), N * N, stdout);
}
int main(int argc, char * argv[])
{
	string input = "input";
	string output = "matr";
	string number = "";
	string extensionIn = ".txt";
	string extensionOut = ".in";
	if (argc > 1)
	{
		input = argv[1];
		if (argc > 2)
		{
			output = argv[2];
			if (argc > 3)
			{
				number = argv[3];
			}
		}
	}

	int N;
	double *A;

	freopen((input + number + extensionIn).c_str(), "r", stdin);
	freopen((output + number + extensionOut).c_str(), "wb", stdout);
	
    cin >> N;
    A = new double[N * N];

	readMatrix(A, N);
	writeMatrixBin(A, N);
}