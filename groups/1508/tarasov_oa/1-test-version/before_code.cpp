#include <cstdio> 
#include <random>

void QuickSort(int* arr, int size);

int main(int argc, char * argv[])
{
	int num_threads = 1;
	if (argc > 1)
		num_threads = atoi(argv[1]);

	int size;
	int* arr;

	freopen("array.in", "rb", stdin);
	freopen("array.out", "wb", stdout);

	fread(&size, sizeof(size), 1, stdin);
	
	arr = new int[size];
	fread(arr, sizeof(*arr), size, stdin);

	//omp_set_num_threads(num_threads);

	//double time = omp_get_wtime();
	QuickSort(arr, size);
	//time = omp_get_wtime() - time;

	//fwrite(&time, sizeof(time), 1, stdout); 
	fwrite(arr, sizeof(*arr), size, stdout);

	return 0;
}