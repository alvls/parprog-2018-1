#include <iostream>
#include <string>
#include "mymatrix.h"
using std::string;
using std::cout;
using std::cin;

bool readMatrixBin(Matrix &A, int N)
{
	int n = (int)fread(A.getP(), sizeof(Element), N * N, stdin);
    if (n != N)
        return false;
    A.transpositionMatrix();
    return true;
}
void writeMatrix(Matrix &A, int N)
{
	for (int i = 0; i < N; i++)
	{
        for (int j = 0; j < N; j++)
            cout << A[i][j]<<' ';
        cout << '\n';
	}
    cout << '\n';
}
int main(int argc, char * argv[])
{
	string inputBinMatrix;
	string outputMatrix;
	string inputBinResMatrix;
	string outputResMatrix;
	string inputBinUserResMatrix;
	string outputUserResMatrix;
    double time = 0.0;
	if (argc > 1)
	{
		inputBinMatrix = argv[1];
		if (argc > 2)
		{
			outputMatrix = argv[2];
			if (argc > 3)
			{
				inputBinResMatrix = argv[3];
				if (argc > 4)
				{
					outputResMatrix = argv[4];
					if (argc > 5)
					{
						inputBinUserResMatrix = argv[5];
						if (argc > 6)
						{
							outputUserResMatrix = argv[6];
						}
					}
				}
			}
		}
	}

	int N;
	freopen(inputBinMatrix.c_str(), "rb", stdin);
    freopen(outputMatrix.c_str(), "w", stdout);
    fread(&N, sizeof(N), 1, stdin);
    Matrix A(N,N);
    cout << N << '\n';
    readMatrixBin(A, N);
    writeMatrix(A, N);
    readMatrixBin(A, N);
    writeMatrix(A, N);

	if (argc > 3)
	{
		freopen(inputBinResMatrix.c_str(), "rb", stdin);
		freopen(outputResMatrix.c_str(), "w", stdout);
		fread(&N, sizeof(N), 1, stdin);
		readMatrixBin(A, N);
		cout << N << '\n';
		writeMatrix(A, N);
	}

	if (argc > 5)
	{
		freopen(inputBinUserResMatrix.c_str(), "rb", stdin);
		freopen(outputUserResMatrix.c_str(), "w", stdout);
		fread(&time, sizeof(time), 1, stdin);
		cout << N << '\n';
		readMatrixBin(A, N);
		writeMatrix(A, N);
		cout << "\ntime = " << time;
	}
}