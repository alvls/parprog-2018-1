#include <iostream>
#include <string>
#include "matrix.h"
using std::string;
using std::cout;
using std::cin;
using std::swap;

bool readMatrix(Matrix &A, int N)
{
    Element x;
    if (!(cin >> x))
        return false;
    A.vv[0] = x;
	for (int i = 1; i < N * N; i++)
	{       
		cin >> A.vv[i];
	}
    A.transpositionMatrix();
    return true;
}
void writeMatrixBin(Matrix &A, int N)
{
	fwrite(A.getP(), sizeof(Element), N*N, stdout);
}
int main(int argc, char * argv[])
{
    string path = "";
    string name = "matr";
    string number = "";
    string extensionIn = ".txt";
    string extensionOut = ".out";
    if (argc > 1)
    {
        path = argv[1];
        path += "/";
        if (argc > 2)
        {
            number = argv[2];
        }
    }


	int N;

	freopen((path + name + number + extensionIn).c_str(), "r", stdin);
    freopen((path+ name + number + extensionOut).c_str(), "wb", stdout);
    cin >> N;
    Matrix A(N, N);
	
    readMatrix(A, N);  
    fwrite(&N, sizeof(N), 1, stdout);
    writeMatrixBin(A, N);

    readMatrix(A, N);
    writeMatrixBin(A, N);
}