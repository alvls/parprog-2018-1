#include <iostream>
#include <string>
#include "matrix.h"
using std::string;
using std::cout;
using std::cin;
using std::swap;

void readMatrix(Matrix &A, int N)
{
	for (int i = 0; i < N * N; i++)
	{
		cin >> A.vv[i];
	}
    A.transpositionMatrix();
}
void writeMatrixBin(Matrix &A, int N)
{
	fwrite(A.getP(), sizeof(Element), N*N, stdout);
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

	freopen((input + number + extensionIn).c_str(), "r", stdin);
	freopen((output + number + extensionOut).c_str(), "wb", stdout);
	
    cin >> N;
    Matrix A(N, N), B(N, N);

	readMatrix(A, N);
    readMatrix(B, N);
    fwrite(&N, sizeof(N), 1, stdout);
	writeMatrixBin(A, N);
    writeMatrixBin(B, N);
}