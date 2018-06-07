#define _CRT_SECURE_NO_WARNINGS

#include <cstdio> 
#include <random>
#include <ctime>
#include <omp.h>
#include <iostream>

void RadixSort(int* arr, const int len);

int main(int argc, char * argv[])
{
    if (argc != 3 || (freopen(argv[1], "rb", stdin)) == NULL) {
        std::cout << "\tRADIX SORT ALGORITHM PROGRAM\n";
        std::cout << "Use the following pattern to use the program:\n";
        std::cout << "\"solver [name of binary file containing your unsorted array] [name of binary file will contains the sorted array]";
        return 1;
    }

    int len;
    int* arr;
    double fict_time;

    freopen(argv[2], "wb", stdout);

    fread(&fict_time, sizeof(fict_time), 1, stdin);
    fread(&len, sizeof(len), 1, stdin);

    arr = new int[len];
    fread(arr, sizeof(*arr), len, stdin);

    double time = omp_get_wtime();
    RadixSort(arr, len);
    time = omp_get_wtime() - time;

    fwrite(&time, sizeof(time), 1, stdout);
    fwrite(&len, sizeof(len), 1, stdout);
    fwrite(arr, sizeof(*arr), len, stdout);

    delete[] arr;
    return 0;
}
