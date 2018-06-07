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
    string path_result;
	string name = "matr";
	string number = "";
	string extensionIn = ".in";
    string extensionInAns = ".ans";
    string extensionInUserAns = ".user.ans";
	string extensionOut = ".txt";
    string extensionOutAns = ".ans.txt";
    double time = 0.0;
	if (argc > 1)
	{
        path = argv[1];
        path_result = path + "_result/";
        path += "/";
		if (argc > 2)
		{
            name = "";
            number = argv[2];			
		}
	}

	int N;
	freopen((path + name + number + extensionIn).c_str(), "rb", stdin);
    freopen((path + name + number + extensionOut).c_str(), "w", stdout);	
    fread(&N, sizeof(N), 1, stdin);
    Matrix A(N,N);
    cout << N << '\n';
    readMatrixBin(A, N);
    writeMatrix(A, N);
    readMatrixBin(A, N);
    writeMatrix(A, N);

    freopen((path + name + number + extensionInAns).c_str(), "rb", stdin);
    freopen((path + name + number + extensionOutAns).c_str(), "w", stdout);
    fread(&N, sizeof(N), 1, stdin);
    readMatrixBin(A, N);
    cout << N << '\n';
    writeMatrix(A, N);

    freopen((path_result + name + number + extensionInUserAns).c_str(), "rb", stdin);
    freopen((path_result + name + number + extensionInUserAns + ".txt").c_str(), "w", stdout);
    fread(&time, sizeof(time), 1, stdin);
    cout << N << '\n';
    readMatrixBin(A, N);
    writeMatrix(A, N);
    cout << "\ntime = " << time;
}