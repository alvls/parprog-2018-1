#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include <cstdio>
#include <string.h>
#include <random>
#include <ctime>
#include <chrono> 
#include <ccomplex>
#include <vector>
#include <iterator>
#include <omp.h>
using namespace std;

const int DEFAULT_MATRIX_SIZE = 10;
const int DEFAULT_DENSITY = 10;  // %

int n_tests[] = { 10,20,30,40,50,60,70,80,90,100,125,150, 200,300,400,500,700,800,900,1000 };

void WriteAnswer(char* input, char* output);

int main(int argc, char* argv[])
{
	char* folder = "../tests/";
	int matrixSize = DEFAULT_MATRIX_SIZE;
	int density = 100 / DEFAULT_DENSITY;
	char* number = "0";
	if (argc > 1)
	{
		number = argv[1];
		matrixSize = n_tests[atoi(argv[1])];
		if (argc > 2)
			if (density > 0 && density < 100)
				density = 100 / atof(argv[2]);
	}
	char *input = new char[strlen(folder) + strlen(number) + 4];
	char *output = new char[strlen(folder) + strlen(number) + 5];
	strcpy(input, folder);
	strcat(input, number);
	strcat(input, ".in");
	strcpy(output, folder);
	strcat(output, number);
	strcat(output, ".ans");

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
			if (i != 0)
			{
				int val = positionA[i - 1];
				positionA.emplace_back(val);
			}
			else
			{
				positionA.emplace_back(0);
			}
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
			if (i != 0)
			{
				int val = positionB[i - 1];
				positionB.emplace_back(val);
			}
			else
			{
				positionB.emplace_back(0);
			}
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
	_fcloseall();
	WriteAnswer(input,output);
	return 0;
}
