//Горожанин М.Ю. 381508. Поразрядная сортировка для целых чисел с четно-нечетным слиянием Бэтчера. Алгоритм сортировки.
#define _CRT_SECURE_NO_WARNINGS

#include "tbb\task_scheduler_init.h"
#include "tbb\parallel_for.h"
#include "tbb\blocked_range.h"
#include "tbb\tbb.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;
using namespace tbb;

double time_error;//Накопление времени которое можно было бы не тратить, если изначально по другому проектировать систему.(Например делать обычную сортировку с массивом а не вектором)

void radix_sort_sol(vector<int>& array_for_sort, const int left_border, const int right_border);

void transformed_sort(int* arr, int size)
{
	tick_count start = tick_count::now();
	vector<int> convert(size);
	for (int i = 0; i < size; i++)
		convert[i] = arr[i];
	tick_count f_st = tick_count::now();
	radix_sort_sol(convert, 0, size - 1);
	tick_count f_fin = tick_count::now();
	for (int i = 0; i < size; i++)
		arr[i]= convert[i];
	tick_count finish = tick_count::now();
	time_error+=((finish - start) - (f_fin - f_st)).seconds();
}

class EvenSelector : public task
{
private:
	int *arr;
	int size1, size2;

public:
	EvenSelector(int* _arr, int _size1, int _size2) : arr(_arr), size1(_size1), size2(_size2) {
	}

	task* execute()
	{
		int* arr2 = arr + size1;

		int num = (size1 + size2 + 1) / 2;
		int* tmp = new int[num];

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

		int num = (size1 + size2) - (size1 + size2 + 1) / 2;
		int* tmp = new int[num];

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
			if (arr[i - 1] > arr[i])
			{
				int tmp = arr[i - 1];
				arr[i - 1] = arr[i];
				arr[i] = tmp;
			}
	}
};

class SortingBody : public task
{
private:
	int *arr;
	int size;
	int portion;

public:
	SortingBody(int *_arr, int _size, int _portion) : arr(_arr), size(_size), portion(_portion) {}

	task* execute()
	{
		if (size <= portion)
		{
			transformed_sort(arr, size);
		}
		else
		{
			int s = size / 2;
			SortingBody &sorter_one = *new (allocate_child()) SortingBody(arr, s, portion);
			SortingBody &sorter_two = *new (allocate_child()) SortingBody(arr + s, size - s, portion);
			set_ref_count(3);
			spawn(sorter_one);
			spawn_and_wait_for_all(sorter_two);
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

void Start_TBB_Sorting(int *arr, int size, int threads)
{
	int portion = size / threads;

	if (size%threads != 0)
		portion++;

	SortingBody& sorter = *new (task::allocate_root())
		SortingBody(arr, size, portion);
	task::spawn_root_and_wait(sorter);
}

int main(int argc, char * argv[])
{
	if (argc != 4) {
		cout << "Enter the correct parameters:" << endl;
		cout << "1. The name of the source binary file" << endl;
		cout << "2. The name of the output binary file" << endl;
		cout << "3. The number of threads" << endl;
		return 1;
	}

	int size, threads = atoi(argv[3]);
	int* arr;
	double fict_time;
	time_error = 0;

	freopen(argv[1], "rb", stdin);
	fread(&fict_time, sizeof(fict_time), 1, stdin);
	fread(&size, sizeof(size), 1, stdin);

	arr = new int[size];
	fread(arr, sizeof(*arr), size, stdin);
	double time;

	tick_count start_main = tick_count::now();
	Start_TBB_Sorting(arr, size, threads);
	tick_count finish_main = tick_count::now();

	time =(finish_main-start_main).seconds()-time_error;
	printf("TBB sorting time: %f\n", time);
	
	freopen(argv[2], "wb", stdout);
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(arr, sizeof(*arr), size, stdout);
	return 0;
}