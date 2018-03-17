#include <omp.h>

void HoaraQuickSort(int* array, int first, int last)
{
	int i = first, j = last;
	int temp, mid = array[(first + last) / 2];

	do {
		while (array[i] < mid)
			i++;
		while (array[j] > mid)
			j--;

		if (i == j)
		{
			i++;
			j--;
		}

			if (i < j)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			i++;
			j--;
		
	} while (i <= j);


	if (i < last)
		HoaraQuickSort(array, i, last);
	if (first < j)
		HoaraQuickSort(array, first, j);
}