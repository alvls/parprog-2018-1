#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <iostream>
using std::vector;

int main(int argc, char* argv[])
{
	char* PATHin = "matr.in";	//default input file name
	char* PATHout = "matr.ans";	//default output file name

	freopen(PATHin, "rb", stdin);
	freopen(PATHout, "wb", stdout);

	int matrixSize = 0;
	int notZero = 0;

	int matrixSizeB = 0;
	int notZeroB = 0;

	//read matrix A
	fread(&matrixSize, sizeof(matrixSize), 1, stdin);
	fread(&notZero, sizeof(notZero), 1, stdin);
	if (notZero == 0)
		throw("Invalid test");

	vector<double> value(notZero);
	vector<int> col(notZero);
	vector<int> row(matrixSize + 1);

	fread(value.data(), sizeof(value[0]), value.size(), stdin);
	fread(col.data(), sizeof(col[0]), col.size(), stdin);
	fread(row.data(), sizeof(row[0]), row.size(), stdin);

	//read matrix B
	fread(&matrixSizeB, sizeof(matrixSizeB), 1, stdin);
	fread(&notZeroB, sizeof(notZeroB), 1, stdin);
	if (notZeroB == 0)
		throw("Invalid test");

	vector<double> valueB(notZeroB);
	vector<int> colB(notZeroB);
	vector<int> rowB(matrixSize + 1);

	fread(valueB.data(), sizeof(valueB[0]), valueB.size(), stdin);
	fread(colB.data(), sizeof(colB[0]), colB.size(), stdin);
	fread(rowB.data(), sizeof(rowB[0]), rowB.size(), stdin);


	if (matrixSize != matrixSizeB) //matrixes are square
		throw("Invalid test");


	vector<vector<double>> standartMatrA(matrixSize);
	vector<vector<double>> standartMatrB(matrixSize);
	vector<vector<double>> standartMatrC(matrixSize);
	for (int i = 0; i < matrixSize; ++i)
	{
		standartMatrA[i].resize(matrixSize);
		standartMatrB[i].resize(matrixSize);
		standartMatrC[i].resize(matrixSize);
	}

	//get matrix A in standard view 
	for (int i = 0; i < matrixSize; ++i)
	{
		int pos = row[i];
		while (pos < row[i + 1])
		{
			standartMatrA[i][col[pos]] = value[pos];
			pos++;
		}
	}

	//get matrix B in standard view 
	for (int i = 0; i < matrixSize; ++i)
	{
		int pos = rowB[i];
		while (pos < rowB[i + 1])
		{
			standartMatrB[i][colB[pos]] = valueB[pos];
			pos++;
		}
	}

	//multiplication
	for (int i = 0; i < matrixSize; ++i)
	{
		for (int j = 0; j < matrixSize; ++j)
		{
			for (int k = 0; k < matrixSize; ++k)
				standartMatrC[i][j] += standartMatrA[i][k] * standartMatrB[k][j];
		}
	}

	fwrite(&matrixSize, sizeof(matrixSize), 1, stdout);
	for (int i = 0; i < standartMatrC.size(); ++i)
		fwrite(standartMatrC[i].data(), sizeof(standartMatrC[i][0]), standartMatrC.size(), stdout);

	//std::cout.precision(10);

	//for (int i = 0; i < matrixSize; ++i)
	//{ 
	//	for (int j = 0; j < matrixSize; ++j)
	//		std::cout << standartMatrA[i][j] << ' ';
	//	std::cout << std::endl;
	//}

	//std::cout << "B----------------------" << std::endl;

	//for (int i = 0; i < matrixSize; ++i)
	//{
	//	for (int j = 0; j < matrixSize; ++j)
	//		std::cout << standartMatrB[i][j] << ' ';
	//	std::cout << std::endl;
	//}

	//std::cout << "C----------------------" << std::endl;

	//for (int i = 0; i < matrixSize; ++i)
	//{
	//	for (int j = 0; j < matrixSize; ++j)
	//		std::cout << standartMatrC[i][j] << ' ';
	//	std::cout << std::endl;
	//}

	return 0;
}
