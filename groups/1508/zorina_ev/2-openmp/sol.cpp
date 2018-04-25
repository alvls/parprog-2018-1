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

		if (i <= j)
		{
			if (i < j)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			i++;
			j--;
		}

	} while (i <= j);


	if (i < last)
		HoaraQuickSort(arr, i, last);
	if (first < j)
		HoaraQuickSort(arr, first, j);
}

void copyArray(int* first, int* last, int* res)
{
	while (first != last + 1)
	{
		(*res) = (*first);
		++first;
		++res;
	}
}


void Merge(int* arr1_begin, int* arr1_end, int* arr2_begin, int* arr2_end, int* dest)
{
	while ((arr1_begin <= arr1_end) && (arr2_begin <= arr2_end))
	{
		auto elem1 = *arr1_begin;
		auto elem2 = *arr2_begin;

		if (elem1 < elem2)
		{
			*dest = elem1;
			++arr1_begin;
		}
		else
		{
			*dest = elem2;
			++arr2_begin;
		}
		++dest;
	}
	if (arr1_begin > arr1_end)
	{
		copyArray(arr2_begin, arr2_end + 1, dest);
	}
	else /*arr2_begin > arr2_end*/
	{
		copyArray(arr1_begin, arr1_end + 1, dest);
	}
}

void HoaraQuickSort_OMP(int* a, int* sorted_a, int n)
{
	int threads_count = omp_get_max_threads();
	int chunk_size = n / threads_count ? n / threads_count : 1;

#pragma omp parallel for
	for (int i = 0; i < threads_count; ++i)
	{
		auto first = i * chunk_size;
		auto last = first + chunk_size - 1;
		HoaraQuickSort(a, first, last);
	}

	auto ret = n % threads_count;
	if (ret)
	{
		HoaraQuickSort(a, threads_count * chunk_size, n - 1);
	}

	//reduction
	int array_size = chunk_size;
	int count = array_size << 1;
	int j = 0;
	while (array_size < n)
	{
		for (j = 0; j <= n - count; j += count)
		{
			int* first_array_start = a + j;
			int* first_array_end = first_array_start + array_size - 1;

			int* second_array_start = a + j + array_size;
			int* secon_array_end = second_array_start + array_size - 1;

			Merge(first_array_start, first_array_end, second_array_start, secon_array_end, sorted_a + j);
		}

		copyArray(sorted_a, sorted_a + j, a);

		array_size = (array_size << 1) > n ? n : array_size << 1;
		count = array_size << 1;
	}

	if (ret)
	{
		int array_size = n - ret;
		int* first_array_start = a;
		int* first_array_end = first_array_start + array_size - 1;

		int* second_array_start = a + array_size;
		int* secon_array_end = second_array_start + ret - 1;

		Merge(first_array_start, first_array_end, second_array_start, secon_array_end, sorted_a);
	}

	copyArray(sorted_a, sorted_a + n, a);
}
