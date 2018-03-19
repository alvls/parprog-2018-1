#include <iostream>
#include <string>
#include "matrix.h"
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
    string path = "";
	string input = "matr";
	string output = "matr";
	string number = "";
	string extensionIn = ".in";
    string extensionInAns = ".ans";
	string extensionOut = ".txt";
    string extensionOutAns = ".ans.txt";
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

    Matrix A(N,N);
    cout << N << '\n';
    readMatrixBin(A, N);
    writeMatrix(A, N);
    readMatrixBin(A, N);
    writeMatrix(A, N);


    freopen((path + input + number + extensionInAns).c_str(), "rb", stdin);
    freopen((path + output + number + extensionOutAns).c_str(), "w", stdout);
    fread(&N, sizeof(N), 1, stdin);

    cout << N << '\n';
    readMatrixBin(A, N);
    writeMatrix(A, N);
}