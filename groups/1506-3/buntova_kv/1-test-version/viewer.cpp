#include <cstdio>
#include "fstream"
#include <iostream>

using namespace std;
FILE *stream;

int main()
{
	double time_ser;
	double res_ser;
	char er = ' ';
	//double time_par;
	//double res_par;
	freopen_s(&stream, "5.ans", "rb", stdin);
	fread(&time_ser, sizeof(time_ser), 1, stdin);
	fread(&res_ser, sizeof(res_ser), 1, stdin);
	fread(&er, sizeof(char), 1, stdin);
	//fread(&time_par, sizeof(time_par), 1, stdin);
	//fread(&res_par, sizeof(res_par), 1, stdin);
	fclose(stream);

	ofstream out("output.txt");
	out << time_ser << endl;
	out << res_ser << endl;
	if (er != ' ')
	{
		out << er;
	}
	
	//out << time_par << endl;
	//out << res_par;
	/*
	int n;
	freopen_s(&stream, "test1.bin", "rb", stdin);
	fread(&n, sizeof(n), 1, stdin);
	double *a = new double[n];
	double *b = new double[n];
	int *func = new int[n];
	int *zn = new int[n];

	fread(func, sizeof(*func), n, stdin);
	fread(zn, sizeof(*zn), n, stdin);
	fread(a, sizeof(*a), n, stdin);
	fread(b, sizeof(*b), n, stdin);
	fclose(stream);

	ofstream out("output.txt");
	out << n << " ";
	for (int i = 0; i < n; i++)
	{
		out << func[i] << " ";
	}
	for (int i = 0; i < n; i++)
	{
		out << zn[i] << " ";
	}
	for (int i = 0; i < n; i++)
	{
		out << a[i] << " ";
	}
	for (int i = 0; i < n; i++)
	{
		out << b[i] << " ";
	}
	freopen_s(&stream, "test1.bin", "wb", stdout);
	fwrite(&n, sizeof(n), 1, stdout);
	fwrite(func, sizeof(*func), n, stdout);
	fwrite(zn, sizeof(*zn), n, stdout);
	fwrite(a, sizeof(*a), n, stdout);
	fwrite(b, sizeof(*b), n, stdout);
	fclose(stream);
	//system("pause");
	*/
	return 0;
}