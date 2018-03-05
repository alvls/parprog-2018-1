#include <iostream>
#include "array_sort.h"
using namespace std;

int main()
{
	const int size = 500;
	int* arr = GenerateArr(size);
	QuickSort(arr, size);
	PrintArray(arr, size);
	return 0;
}
