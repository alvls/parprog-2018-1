#include <iostream>
#include <string>
#include "matrix.h"
using std::string;
using std::cout;
using std::cin;

void readMatrixBin(Matrix &A, int N)
{
	fread(A.getP(), sizeof(Element), N * N, stdin);
    A.transpositionMatrix();
}
void writeMatrix(Matrix &A, int N)
{
    cout << N << '\n';
	for (int i = 0; i < N; i++)
	{
        for (int j = 0; j < N; j++)
            cout << A[i][j];
        cout << '\n';
	}
}
int main(int argc, char * argv[])
{
	string input = "matr";
	string output = "output";
	string number = "";
	string extensionIn = ".in";
	string extensionOut = ".txt";
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

	freopen((input + number + extensionIn).c_str(), "rb", stdin);
	freopen((output + number + extensionOut).c_str(), "w", stdout);
	
    fread(&N, sizeof(N), 1, stdin);
    Matrix A(N,N);
	
    readMatrixBin(A, N);
	writeMatrix(A, N);
}