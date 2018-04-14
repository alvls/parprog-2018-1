#define _CRT_SECURE_NO_WARNINGS

#include <omp.h>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <vector>

void QuickSort(int* arr, int size);

void MergeAndSort(const std::vector<int> vec1, const std::vector<int> vec2, int* write_to)
{
	int i = 0, j = 0;
	int size1 = vec1.size(), size2 = vec2.size();

	while (i < size1 && j < size2) {
		write_to[i + j] = vec1[i];
		write_to[i + j + 1] = vec2[j];
		++i; ++j;
	}

	while (i < size1) {
		write_to[size2 + i] = vec1[i];
		i++;
	}
	while (j < size2) {
		write_to[size1 + j] = vec2[j];
		j++;
	}
	
	i = 1; // Первый элемент проверять не нужно
	while (i < size1 + size2 - 1) {
		if (write_to[i] > write_to[i + 1]) {
			j = write_to[i];
			write_to[i] = write_to[i + 1];
			write_to[i + 1] = j;
		}
		++i;
	}
}

enum elemType {
	EVEN,
	ODD
};


void SelectElements(elemType type, const int* arr1, int size1, const int* arr2, int size2, std::vector<int>& result) {
	int i, j;
	if (type == EVEN) i = 0, j = 0;
	else i = 1, j = 1;
	result.reserve(size1+size2);
	while (i < size1 && j < size2) {	
		if (arr1[i] <= arr2[j])
		{
			result.push_back(arr1[i]);
			i += 2;
		}
		else
		{
			result.push_back(arr2[j]);
			j += 2;
		}
	}
	if (i >= size1)
		while (j < size2) {
			result.push_back(arr2[j]);
			j += 2;
		}
	else
		while (i < size1) {
			result.push_back(arr1[i]);
			i += 2;
		}
}


int main(int argc, char * argv[])
{
	if (argc != 4) {
		std::cout << "Use 'omp_qs [threads] [input file] [output file]'" << std::endl;
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
	int step;
	std::vector<int>* tempArray = new std::vector<int>[threads];
	int *shift = new int[threads], *chunk = new int[threads];
	#pragma omp parallel shared(arr, step, shift, chunk, tempArray) num_threads(threads) 
	{
		int tid, thread_index;
		tid = omp_get_thread_num();
		
		shift[tid] = tid*(size / threads);
		chunk[tid] = (tid == threads - 1) ? size - tid * (size / threads) : size / threads;
		QuickSort(arr + shift[tid], chunk[tid]);
		#pragma omp barrier

		step = 1;
		while (step < threads) {
			thread_index = (int)pow(2, step - 1);

			if (tid % (thread_index*2) == 0) {
				SelectElements(EVEN, arr + shift[tid], chunk[tid], arr + shift[tid + thread_index], chunk[tid + thread_index], tempArray[tid]);
			}
			else if(tid % thread_index == 0) {
				SelectElements(ODD, arr + shift[tid], chunk[tid], arr + shift[tid - thread_index], chunk[tid - thread_index], tempArray[tid]);
			}
			#pragma omp barrier
			if (tid % (thread_index*2) == 0) {
				MergeAndSort(tempArray[tid], tempArray[tid + thread_index], arr + shift[tid]);
				chunk[tid] += chunk[tid + thread_index];
				tempArray[tid].clear(); tempArray[tid].shrink_to_fit();
				tempArray[tid + thread_index].clear(); tempArray[tid + thread_index].shrink_to_fit();
			}
			#pragma omp single 
			{
				step *= 2;
			}
			#pragma omp barrier
		}
	}
	delete[] tempArray;
	delete[] chunk;
	delete[] shift;
	
	time = omp_get_wtime() - time;
	printf("OpenMP time: %f\n", time);

	freopen(argv[3], "wb", stdout);
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(arr, sizeof(*arr), size, stdout);
	return 0;
}
