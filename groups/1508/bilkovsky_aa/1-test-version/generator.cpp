#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include <cstdio>
#include <random>
#include <ctime>
#include <chrono> 
#include <ccomplex>
#include <vector>
#include <iterator>
using namespace std;

const int DEFAULT_MATRIX_SIZE = 100;
const int DEFAULT_DENSITY = 10;  // %

int n_tests[] = { 10, 20,50,100, 150, 200, 400,500, 700, 1000 };

int main(int argc, char* argv[])
{
	char* input = "../matr.in";
	int matrixSize = DEFAULT_MATRIX_SIZE;
	int density = 100 / DEFAULT_DENSITY;
	if (argc > 1)
	{
		input = argv[1];
		if (argc > 2)
		{
			matrixSize = n_tests[atoi(argv[2])];
			if (argc > 3)
				if (density > 0 && density < 100)
					density = 100 / atof(argv[3]);
		}
	}
	vector<complex<int>> elementsA, elementsB;
	vector<int> secondIndexA, secondIndexB, positionA, positionB;

	freopen(input, "wb", stdout);

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
				secondIndexA.emplace_back(j);
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
				secondIndexB.emplace_back(j);
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

	int notNullA = elementsA.size();
	fwrite(&matrixSize, sizeof(matrixSize), 1, stdout);
	fwrite(&notNullA, sizeof(notNullA), 1, stdout);
	complex<int> *elements1 = new complex<int>[notNullA];
	copy(elementsA.begin(), elementsA.end(), elements1);
	int *secondIndex1 = new int[notNullA];
	int *position1 = new int[matrixSize + 1];
	copy(secondIndexA.begin(), secondIndexA.end(), secondIndex1);
	copy(positionA.begin(), positionA.end(), position1);
	fwrite(elements1, sizeof(*elements1), notNullA, stdout);
	fwrite(secondIndex1, sizeof(*secondIndex1), notNullA, stdout);
	fwrite(position1, sizeof(*position1), matrixSize + 1, stdout);

	int notNullB = elementsB.size();
	fwrite(&notNullB, sizeof(notNullB), 1, stdout);
	complex<int> *elements2 = new complex<int>[notNullB];
	copy(elementsB.begin(), elementsB.end(), elements2);
	int *secondIndex2= new int[notNullB];
	int *position2 = new int[matrixSize + 1];
	copy(secondIndexB.begin(), secondIndexB.end(), secondIndex2);
	copy(positionB.begin(), positionB.end(), position2);
	fwrite(elements2, sizeof(*elements2), notNullB, stdout);
	fwrite(secondIndex2, sizeof(*secondIndex2), notNullB, stdout);
	fwrite(position2, sizeof(*position2), matrixSize + 1, stdout);
	return 0;
}
