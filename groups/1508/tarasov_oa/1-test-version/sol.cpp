#include <random>
#include <iostream>
using namespace std;

void QuickSort(int* arr, int size)
{
	int i = 0, j = size - 1;
	int pivot = arr[size / 2];

	do {
		while (arr[i] < pivot) i++;
		while (arr[j] > pivot) j--;

		if (i <= j) {
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;

			i++;
			j--;
		}
	} while (i <= j);


	if (j > 0)
		QuickSort(arr, j + 1);
	if (i < size)
		QuickSort(&arr[i], size - i);
}


int* GenerateArr(int size)
{
	int* arr = new int[size];
	for (int i = 0; i < size; ++i)
		arr[i] = rand() % 1000;

	return arr;
}

void PrintArray(int* arr, int size)
{
	std::cout << "{ ";
	for (int i = 0; i < size; ++i)
		std::cout << arr[i] << " ";
	std::cout << " }" << std::endl;
}