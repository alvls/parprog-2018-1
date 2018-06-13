#include <cstdio>
#include "fstream"
#include <iostream>

using namespace std;
FILE *stream;

int main()
{
	int n;
	ifstream in("input.txt");
	in >> n;
	int *func = new int[n];
	int *zn = new int[n];
	double *a = new double[n];
	double *b = new double[n];
	for (int i = 0; i < n; i++)
	{
		in >> func[i];
	}
	for (int i = 0; i < n; i++)
	{
		in >> zn[i];
	}
	for (int i = 0; i < n; i++)
	{
		in >> a[i];
	}
	for (int i = 0; i < n; i++)
	{
		in >> b[i];
	}
	freopen_s(&stream, "5", "wb", stdout);
	fwrite(&n, sizeof(n), 1, stdout);
	fwrite(func, sizeof(*func), n, stdout);
	fwrite(zn, sizeof(*zn), n, stdout);
	fwrite(a, sizeof(*a), n, stdout);
	fwrite(b, sizeof(*b), n, stdout);
	fclose(stream);
	//system("pause");
	return 0;
}