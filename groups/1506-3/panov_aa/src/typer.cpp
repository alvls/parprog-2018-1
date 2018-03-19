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
	string input = "input";
	string output = "matr";
	string number = "";
	string extensionIn = ".txt";
	string extensionOut = ".in";
	if (argc == 2)
	{
		number = argv[1];
        input = "";
        output = "";
        extensionIn = "";
        extensionOut = "";
	}
    else
    {
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

	freopen((path + input + number + extensionIn).c_str(), "r", stdin);
    cin >> N;
    Matrix A(N, N);
	readMatrix(A, N);
    Matrix B(N, N);
    if (readMatrix(B, N) == false)
    {
        extensionOut = ".ans";
    }

    freopen((output + number + extensionOut).c_str(), "wb", stdout);
    fwrite(&N, sizeof(N), 1, stdout);
    writeMatrixBin(A, N);
    if (extensionOut != ".ans")
        writeMatrixBin(B, N);
}