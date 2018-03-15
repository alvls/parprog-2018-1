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