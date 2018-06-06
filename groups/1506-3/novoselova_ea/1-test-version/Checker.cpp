#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <string>
#include <fstream>
#include<iostream>
using namespace std;


int MUL(int *MatrixA, int *MatrixB, int *MatrixC, int N);

int main(int argc, char *argv[])
{
	char *filein = "1";
	char *fileout = "1.ans";
	if (argc > 1)
	{
		filein = argv[1];
		fileout = argv[2];
	}

	int n;
	double time;
	int *a, *b, *ans, *res;
	freopen(filein, "rb", stdin);
	fread(&n, sizeof(n), 1, stdin);
	a = new int[n * n];
	b = new int[n * n];
	fread(a, sizeof(*a), n * n, stdin);
	fread(b, sizeof(*b), n * n, stdin);
	fclose(stdin);
	res = new int[n * n];
	ans = new int[n * n];
	freopen(fileout, "rb", stdin);
	fread(&time, sizeof(time), 1, stdin);
	fread(&n, sizeof(n), 1, stdin);
	fread(res, sizeof(*res), n * n, stdin);
	fclose(stdin);
	MUL(a, b, ans, n);
	double diff = 0.0;
	for (int i = 0; i < n * n; i++)
		diff += (ans[i] - res[i]) * (ans[i] - res[i]);
	
	std::ofstream resultFile("result.txt");
	if (diff < 0.0001)
	{
		if (resultFile.is_open())
		{

			resultFile << "AC. Numbers are equal";
		}
		
	}
	else
	{
		if (resultFile.is_open())
		{

			resultFile << "WA. Output is not correct";
		}
	}
	return 0;
}