#define _CRT_SECURE_NO_WARNINGS

#include "tbb\task_scheduler_init.h"
#include "tbb\parallel_for.h"
#include "tbb\blocked_range.h"
#include "tbb\tbb.h"
#include <omp.h>
#include <iostream>
#include <cstdio>
#include <string>


using namespace tbb;

void QuickSort(int* arr, int size);

class EvenSelector : public task
{
private:
	int *arr;
	int size1, size2;

public: 
	EvenSelector (int* _arr, int _size1, int _size2) : arr(_arr), size1(_size1), size2(_size2) {
	}

	task* execute()
	{
		int* arr2 = arr + size1;

		int num = (size1 + size2 + 1) / 2; // Число четных элементов
		int* tmp = new int[num]; // Массив для хранения четных элементов
		
		int a = 0, b = 0, i = 0;
		while (a < size1 && b < size2) {
			if (arr[a] <= arr2[b])
			{
				tmp[i] = arr[a];
				a += 2;
			}
			else
			{
				tmp[i] = arr2[b];
				b += 2;
			}
			i++;
		}

		if (a >= size1)
			for (int j = b; j < size2; j += 2, i++)
				tmp[i] = arr2[j];
		else
			for (int j = a; j < size1; j += 2, i++)
				tmp[i] = arr[j];

		// Копирование из временного массива в основной
		for (int j = 0; j < num; ++j)
			arr[j * 2] = tmp[j];
		return NULL;
	}
};

class OddSelector : public task
{
private:
	int *arr;
	int size1, size2;

public:
	OddSelector(int* _arr, int _size1, int _size2) : arr(_arr), size1(_size1), size2(_size2) {
	}

	task* execute()
	{
		int* arr2 = arr + size1;

		int num = (size1 + size2) - (size1 + size2 + 1) / 2; // Число нечетных элементов
		int* tmp = new int[num]; // Массив для хранения четных элементов

		int a = 1, b = 1, i = 0;
		while (a < size1 && b < size2) {
			if (arr[a] <= arr2[b])
			{
				tmp[i] = arr[a];
				a += 2;
			}
			else
			{
				tmp[i] = arr2[b];
				b += 2;
			}
			i++;
		}

		if (a >= size1)
			for (int j = b; j < size2; j += 2, i++)
				tmp[i] = arr2[j];
		else
			for (int j = a; j < size1; j += 2, i++)
				tmp[i] = arr[j];
	
		// Копирование из временного массива в основной
		for (int j = 0; j < num; ++j)
			arr[j * 2 + 1] = tmp[j];
		return NULL;
	}
};


class Comparator
{
private:
	int *arr;
public:
	Comparator(int *_arr) : arr(_arr) {}

	void operator()(const blocked_range<int>& r) const
	{
		int begin = r.begin(), end = r.end();
		for (int i = begin; i<end; i++)
			if (arr[i-1] > arr[i])
			{
				int tmp = arr[i-1];
				arr[i-1] = arr[i];
				arr[i] = tmp;
			}
	}
};

class Sorter: public task
{
private:
	int *arr;
	int size;
	int portion;

public:
	Sorter(int *_arr, int _size, int _portion) : arr(_arr), size(_size), portion(_portion) {}

	task* execute()
	{
		if (size <= portion)
		{
			QuickSort(arr, size);
		}
		else
		{
			int s = size / 2 + (size / 2) % 2;
			Sorter &sorter1 = *new (allocate_child()) Sorter(arr, s, portion);
			Sorter &sorter2 = *new (allocate_child()) Sorter(arr + s, size - s, portion);
			set_ref_count(3);
			spawn(sorter1);
			spawn_and_wait_for_all(sorter2);
			EvenSelector &evenSelector = *new (allocate_child()) EvenSelector(arr, s, size - s);
			OddSelector &oddSelector = *new (allocate_child()) OddSelector(arr, s, size - s);
			set_ref_count(3);
			spawn(evenSelector);
			spawn_and_wait_for_all(oddSelector);

			parallel_for(blocked_range<int>(1, size), Comparator(arr));
		}
		return NULL;
	}
};

void TBB_QS(int *arr, int size, int threads)
{
	int portion = size / threads + 1;
	Sorter& sorter = *new (task::allocate_root())
		Sorter(arr, size, portion);
	task::spawn_root_and_wait(sorter);
}


int main(int argc, char * argv[])
{
	if (argc != 4) {
		std::cout << "Use 'tbb_qs [threads] [input file] [output file]'" << std::endl;
		return 1;
	}

	int size, threads = atoi(argv[1]);
	int* arr;
	double fict_time;

	freopen(argv[2], "rb", stdin);
	fread(&fict_time, sizeof(fict_time), 1, stdin);
	fread(&size, sizeof(size), 1, stdin);

	arr = new int[size];
	fread(arr, sizeof(*arr), size, stdin);
	double time = omp_get_wtime();

	TBB_QS(arr, size, threads);

	time = omp_get_wtime() - time;
	printf("TBB time: %f\n", time);

	freopen(argv[3], "wb", stdout);
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(arr, sizeof(*arr), size, stdout);
	return 0;
}