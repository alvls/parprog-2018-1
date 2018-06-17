#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
#include <ccomplex>
#include <msxml.h>
#include<ctime>
#include "Matrix.h"
#include "tbb\parallel_for.h"
using namespace std;

Matrix Calculate(int size, int notNull1, complex<int> *elements1, int *secondIndex1, int *position1, int notNull2, complex<int> *elements2, int *secondIndex2, int *position2, char *output, int threds_number);


int main(int argc, char* argv[])
{
    int threads_number = 1;
    char* folder = "../tests/";
    char *number = "0";
    char *input = new char[strlen(folder) + strlen(number) + 4];
    char *output = new char[strlen(folder) + strlen(number) + 5];
    if (argc > 1)
    {
        number = argv[1];
        if (argc > 2)
        {
            threads_number = atoi(argv[2]);
        }
    }
    strcpy(input, folder);
    strcat(input, number);
    strcat(input, ".in");
    strcpy(output, folder);
    strcat(output, number);
    strcat(output, ".out");
    int size, notNull1, notNull2;
    complex<int>* elements1, *elements2;
    int *secondIndex1, *secondIndex2, *position1, *position2;

    freopen(input, "rb", stdin);
    freopen(output, "wb", stdout);

    fread(&size, sizeof(size), 1, stdin);
    fread(&notNull1, sizeof(notNull1), 1, stdin);

    elements1 = new complex<int>[notNull1];
    secondIndex1 = new int[notNull1];
    position1 = new int[size + 1];

    fread(elements1, sizeof(*elements1), notNull1, stdin);
    fread(secondIndex1, sizeof(*secondIndex1), notNull1, stdin);
    fread(position1, sizeof(*position1), size + 1, stdin);

    fread(&notNull2, sizeof(notNull2), 1, stdin);

    elements2 = new complex<int>[notNull2];
    secondIndex2 = new int[notNull2];
    position2 = new int[size + 1];

    fread(elements2, sizeof(*elements2), notNull2, stdin);
    fread(secondIndex2, sizeof(*secondIndex2), notNull2, stdin);
    fread(position2, sizeof(*position2), size + 1, stdin);
    double timeS = clock();
    Matrix result = Calculate(size, notNull1, elements1, secondIndex1, position1, notNull2, elements2, secondIndex2, position2, output, threads_number);
    double timeF = clock();
    result.WriteMatrix(output, timeF - timeS);

    return 0;
}
