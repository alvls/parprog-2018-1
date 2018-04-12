//Горожанин М.Ю. 381508. Поразрядная сортировка для целых чисел с четно-нечетным слиянием Бэтчера. Алгоритм сортировки.
#define _CRT_SECURE_NO_WARNINGS
//
//Алгоритм основан на версии слияния "Чётно-нечетное слияние Бэтчера" из работы http://hpc-education.unn.ru/files/courses/XeonPhi/Lab07.pdf
//Адаптирован под OMP
//

#include <omp.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <random>
#include <chrono>

void radix_sort_sol(std::vector<int>& array_for_sort, const int left_border, const int right_border);
//
//Слияние векторов четных и нечетных элементов первоначального массива
//
void MergeAndSort(const std::vector<int> vec_one, const std::vector<int> vec_two, int* output_sorted_array)
{
	int i = 0, j = 0;
	int size1 = vec_one.size(), size2 = vec_two.size();

	while (i < size1 && j < size2) {
		output_sorted_array[i + j] = vec_one[i];
		output_sorted_array[i + j + 1] = vec_two[j];
		++i; ++j;
	}

	while (i < size1) {
		output_sorted_array[size2 + i] = vec_one[i];
		i++;
	}
	while (j < size2) {
		output_sorted_array[size1 + j] = vec_two[j];
		j++;
	}
	//
	//Чтобы массив стал окончательно отсортированным, достаточно сравнить
	//пары элементов, стоящие на нечётной и чётной позициях.
	//Первый и последний элементы массива проверять не надо, 
	//т.к.они являются минимальным и максимальным элементами массивов.
	//Взято из пояснения к алгоритму слияния.
	//
	i = 1;
	while (i < size1 + size2 - 1) {
		if (output_sorted_array[i] > output_sorted_array[i + 1]) {
			j = output_sorted_array[i];
			output_sorted_array[i] = output_sorted_array[i + 1];
			output_sorted_array[i + 1] = j;
		}
		++i;
	}
}

enum elemType {
	EVEN,
	ODD
};
//
//Выделение из двух массивов четных или нечетных элементов (в упорядоченном виде)
//
void select_splitter(elemType type, const int* array_one, int size_one, const int* array_two, int size_two, std::vector<int>& result) {
	int i, j;
	if (type == EVEN)
	{
		i = 0;
		j = 0;
	}
	else
	{
		i = 1;
		j = 1;
	}
	result.reserve(size_one + size_two);
	while (i < size_one && j < size_two) {
		if (array_one[i] <= array_two[j])
		{
			result.push_back(array_one[i]);
			i += 2;
		}
		else
		{
			result.push_back(array_two[j]);
			j += 2;
		}
	}
	if (i >= size_one)
		while (j < size_two) {
			result.push_back(array_two[j]);
			j += 2;
		}
	else
		while (i < size_one) {
			result.push_back(array_one[i]);
			i += 2;
		}
}


void parallel_sort(std::vector<int>& vector_for_sorting, int _size, int _threads, double& _time)
{
	int size = _size, threads = _threads;
	std::vector<int> vec_for_sort = vector_for_sorting;

	int* arr = new int[size];
	int step;
	std::vector<int>* typed_array = new std::vector<int>[threads];
	int* shift = new int[threads];
	int* dimension = new int[threads];
	double time = omp_get_wtime();
#pragma omp parallel shared(arr, step, shift, dimension, typed_array) num_threads(threads)
	{
		int t_id, thread_change;
		t_id = omp_get_thread_num();

		shift[t_id] = t_id * (size / threads);
		if (t_id == threads - 1)
			dimension[t_id] = size - t_id * (size / threads);
		else
			dimension[t_id] = size / threads;
		radix_sort_sol(vec_for_sort, shift[t_id], shift[t_id] + dimension[t_id] - 1);
#pragma omp barrier
#pragma omp single
		{
			for (int k = 0; k < size; k++) {
				arr[k] = vec_for_sort[k];
				//std::cout << vec_for_sort[k];
			}
			//std::cout << std::endl;
		}
		step = 1;
		while (step < threads)
		{
			thread_change = step;

			if (t_id % (thread_change * 2) == 0)
				select_splitter(EVEN, arr + shift[t_id], dimension[t_id], arr + shift[t_id + thread_change], dimension[t_id + thread_change],
					typed_array[t_id]);
			else if (t_id % thread_change == 0)
				select_splitter(ODD, arr + shift[t_id], dimension[t_id], arr + shift[t_id - thread_change], dimension[t_id - thread_change],
					typed_array[t_id]);
#pragma omp barrier
			if (t_id % (thread_change * 2) == 0)
			{
				MergeAndSort(typed_array[t_id], typed_array[t_id + thread_change], arr + shift[t_id]);
				dimension[t_id] += dimension[t_id + thread_change];
				typed_array[t_id].clear();
				typed_array[t_id].shrink_to_fit();
				typed_array[t_id + thread_change].clear();
				typed_array[t_id + thread_change].shrink_to_fit();
			}
#pragma omp single
			{
				step *= 2;
			}
#pragma omp barrier
		}
	}
	_time = omp_get_wtime() - time;
	delete[] typed_array;
	delete[] dimension;
	delete[] shift;
	for (int k = 0; k < size; k++) {
		vector_for_sorting[k] = arr[k];
	}
}

