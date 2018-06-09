#define _CRT_SECURE_NO_WARNINGS
#include <omp.h>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <vector>
using namespace std;

void qSort_array_recursion(double* arr, int size);

void MergeAndSort(const std::vector<double> vec1, const std::vector<double> vec2, double* write_to) //функция сортировки и слияния двух векторов
{
	int i = 0, j = 0;
	int size1 = vec1.size(), size2 = vec2.size();
	//write_to = new double[size1 + size2];

	while (i < size1 && j < size2) {
		if (vec1[i] <= vec2[j]) {
			write_to[i + j] = vec1[i];
			i++;
		}
		else {
			write_to[i + j] = vec2[j];
			j++;
		}
	}

	while (i < size1) {
		write_to[size2 + i] = vec1[i];
		i++;
	}
	while (j < size2) {
		write_to[size1 + j] = vec2[j];
		j++;
	}
}

int main(int argc, char * argv[])
{
	if (argc != 4) {
		std::cout << "Use 'omp_qs [threads] [input file] [output file]'" << std::endl;
		return 1;
	}

	int size,
		threads = atoi(argv[1]);
	double* arr;
	double fict_time;

	freopen(argv[2], "rb", stdin);
	fread(&fict_time, sizeof(fict_time), 1, stdin);
	fread(&size, sizeof(size), 1, stdin);

	arr = new double[size];

	fread(arr, sizeof(*arr), size, stdin);

	double time = omp_get_wtime();
	int step;
	std::vector<double>* tempArray = new std::vector<double>[threads]; //массив 4х векторов 
	int *shift = new int[threads], *chunk = new int[threads]; //сдвиг относительно начала, хвост относительно сдвига
#pragma omp parallel shared(arr, step, shift, chunk, tempArray) num_threads(threads) 
	{
		int tid, thread_index; //ид текущего потока 
		tid = omp_get_thread_num();

		shift[tid] = tid*(size / threads); //начало с которого будем сортировать
		chunk[tid] = (tid == threads - 1) ? size - tid * (size / threads) : size / threads;
		qSort_array_recursion(arr + shift[tid], chunk[tid]);

#pragma omp barrier //ждешь все потоки

		step = 1; //шаг рекурсии
		while (step < threads) {
			thread_index = (int)pow(2, step - 1); //позволяет найти следующиий поток
			for (int i = 0; i < chunk[tid]; ++i) { //записываю каждый кусох исходного массива в нужный вектор
				tempArray[tid].push_back(*(arr + shift[tid] + i));
			}

#pragma omp barrier //ждем все потоки
			if (tid % (thread_index * 2) == 0) { //в каждой паре берем левый 
				MergeAndSort(tempArray[tid], tempArray[tid + thread_index], &arr[shift[tid]]);
				chunk[tid] += chunk[tid + thread_index];
				tempArray[tid].clear(); tempArray[tid].shrink_to_fit(); //удаление памяти
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