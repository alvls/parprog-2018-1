#include <iostream>
#include <ccomplex>
#include <msxml.h>
#include "Matrix.h"
using namespace std;

Matrix Calculate(Matrix a1, Matrix a2);


int main(int argc, char* argv[])
{
	char* input = "matr.in";
	char* output = "matr.out";

	int size, notNull1, notNull2;
	complex<int>* elements1, *elements2;
	int *secondIndex1, *secondIndex2, *position1, *position2;

	fread(&size, sizeof(size), 1, stdin);
	fread(&notNull1, sizeof(notNull1), 1, stdin);

	elements1 = new complex<int>[notNull1];
	secondIndex1 = new int[notNull1];
	position1 = new int[size + 1];

	fread(&elements1, sizeof(*elements1), notNull1, stdin);
	fread(&secondIndex1, sizeof(*secondIndex1), notNull1, stdin);
	fread(&position1, sizeof(*position1), size + 1, stdin);

	fread(&notNull2, sizeof(notNull2), 1, stdin);

	elements2 = new complex<int>[notNull2];
	secondIndex2 = new int[notNull2];
	position2 = new int[size + 1];

	fread(&elements2, sizeof(*elements2), notNull2, stdin);
	fread(&secondIndex2, sizeof(*secondIndex2), notNull2, stdin);
	fread(&position2, sizeof(*position2), size + 1, stdin);

	Matrix matr1(size, notNull1, elements1, secondIndex1, position1), matr2(size, notNull2, elements2, secondIndex2, position2);
	Matrix result = matr1 * matr2;

	return 0;
}
