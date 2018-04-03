#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <random>
#include <ctime>
#include <chrono> 
#include <ccomplex>
#include <vector>
using namespace std;

const int DEFAULT_MATRIX_SIZE = 1000;
const int DEFAULT_DENSITY = 10;  // %

int n_tests[] = { 10, 20,50,100, 150, 200, 400,500, 700, 1000 };

int main(int argc, char* argv[])
{
	char* inputPath = "matr.in";
	int matrixSize = DEFAULT_MATRIX_SIZE;
	int density = 100 / DEFAULT_DENSITY;
	if (argc > 1)
	{
		inputPath = argv[1];
		if (argc > 2)
		{
			matrixSize = n_tests[atoi(argv[2])];
			if (argc > 3)
				density = 100 / atof(argv[3]);
		}
	}
	vector<complex<int>> elementsA, elementsB;
	vector<int> secondIndexA, secondIndexB, positionA, positionB;

	freopen(inputPath, "wb", stdout);

	for (int i = 0; i < matrixSize; i++)
	{
		bool first = true;
		for (int j = 0; j < matrixSize; j++)
		{
			int isElement = rand() % density + 1;
			if (isElement == 1)
			{
				complex<int> element;
				element.real(rand() % 1000 + 1);
				element.imag(rand() % 1000 + 1);
				elementsA.emplace_back(element);
				secondIndexA.emplace_back(j + 1);
				if (first)
				{
					first = false;
					positionA.emplace_back(elementsA.size());
				}
			}
		}
		if (first)
		{
			positionA.emplace_back(positionA.at(positionA.size()));
		}
	}
	positionA.emplace_back(elementsA.size());

	for (int i = 0; i < matrixSize; i++)
	{
		bool first = true;
		for (int j = 0; j < matrixSize; j++)
		{
			int isElement = rand() % density + 1;
			if (isElement == 1)
			{
				complex<int> element;
				element.real(rand() % 1000 + 1);
				element.imag(rand() % 1000 + 1);
				elementsB.emplace_back(element);
				secondIndexB.emplace_back(j + 1);
				if (first)
				{
					first = false;
					positionB.emplace_back(elementsB.size());
				}
			}
		}
		if (first)
		{
			positionB.emplace_back(positionB.at(positionB.size()));
		}
	}
	positionB.emplace_back(elementsB.size());

	int notNull = matrixSize * matrixSize - elementsA.size();
	fwrite(&matrixSize, sizeof(matrixSize), 1, stdout);
	fwrite(&notNull, sizeof(notNull), 1, stdout);
	fwrite(elementsA.data(), sizeof(elementsA[0]), elementsA.size(), stdout);
	fwrite(secondIndexA.data(), sizeof(secondIndexA[0]), secondIndexA.size(), stdout);
	fwrite(positionA.data(), sizeof(positionA[0]), positionA.size(), stdout);
	notNull = matrixSize * matrixSize - elementsB.size();
	fwrite(&notNull, sizeof(notNull), 1, stdout);
	fwrite(elementsA.data(), sizeof(elementsA[0]), elementsA.size(), stdout);
	fwrite(secondIndexA.data(), sizeof(secondIndexA[0]), secondIndexA.size(), stdout);
	fwrite(positionA.data(), sizeof(positionA[0]), positionA.size(), stdout);
	return 0;
}