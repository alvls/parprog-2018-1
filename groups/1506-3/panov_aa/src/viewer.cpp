#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
void readMatrixBin(double *A, int N)
{
	fread(A, sizeof(*A), N * N, stdin);
}
void writeMatrix(double *A, int N)
{
    cout << N << '\n';
	for (int i = 0; i < N*N; i++)
	{
		cout << A[i] << ' ';
        if ((i + 1) % N == 0)
        {
            cout << '\n';
        }
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
	double *A;

	freopen((input + number + extensionIn).c_str(), "rb", stdin);
	freopen((output + number + extensionOut).c_str(), "w", stdout);
	
    fread(&N, sizeof(N), 1, stdin);
	A = new double[N * N];
	
    readMatrixBin(A, N);
	writeMatrix(A, N);
}