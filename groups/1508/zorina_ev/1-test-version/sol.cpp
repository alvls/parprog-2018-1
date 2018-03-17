#include <omp.h>

void HoaraQuickSort(int* arr, int first, int last)
{
	int i = first, j = last;
	int temp, mid = arr[(first + last) / 2];

	do {
		while (arr[i] < mid)
			i++;
		while (arr[j] > mid)
			j--;

		if (i == j)
		{
			i++;
			j--;
		}

			if (i < j)x
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			i++;
			j--;
		
	} while (i <= j);


	if (i < last)
		HoaraQuickSort(arr, i, last);
	if (first < j)
		HoaraQuickSort(arr, first, j);
}