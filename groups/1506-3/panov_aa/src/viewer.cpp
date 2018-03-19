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
	for (int i = 0; i < N; i++)
	{
        for (int j = 0; j < N; j++)
            cout << A[i][j]<<' ';
        cout << '\n';
	}
}
int main(int argc, char * argv[])
{
    string path = "";
	string input = "matr";
	string output = "output";
	string number = "";
	string extensionIn = ".in";
	string extensionOut = ".txt";
	if (argc > 1)
	{
        path = argv[1];
		if (argc > 2)
		{
            number = argv[2];			
		}
	}

	int N;

	freopen((path + input + number + extensionIn).c_str(), "rb", stdin);
	freopen((path + output + number + extensionOut).c_str(), "w", stdout);
	
    fread(&N, sizeof(N), 1, stdin);
    Matrix A(N,N), B(N,N);
	
    readMatrixBin(A, N);
    readMatrixBin(B, N);
    cout << N << '\n';
	writeMatrix(A, N);
    cout << '\n';
    writeMatrix(B, N);
}