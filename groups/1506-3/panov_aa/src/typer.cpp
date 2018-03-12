#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;

void readMatrix(double *A, int N)
{
	for (int i = 0; i < N*N; i++)
	{
		cin >> A[i];
	}
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
	string extensionOut = ".out";
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