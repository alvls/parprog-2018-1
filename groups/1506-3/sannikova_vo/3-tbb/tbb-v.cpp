#define _CRT_SECURE_NO_WARNINGS
#include "tbb\task_scheduler_init.h"
#include "tbb\parallel_for.h"
#include "tbb\blocked_range.h"
#include <string.h>
#include <string>
#include <cstdio>
#include "tbb\tbb.h"
#include <iostream>
#include <stdio.h>
#include <omp.h>
using namespace tbb;
using namespace std;

void QuickSort(double* arr, int size)
{
	int i = 0, j = size - 1;
	double pivot = arr[size / 2];

	do {
		while (arr[i] < pivot) i++;
		while (arr[j] > pivot) j--;

		if (i <= j) {
			double tmp = arr[i];
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

void printArray(double* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << "|" << endl;
}

class ParallelSorter : public task { //рекурсивное слияние и сортировка
private:
	double* mas; //исходный массив
	int size; //размер
	int portion; //порция
	void MergeAndSort(int size1, int size2) //слияние двух подряд идущих отсортированных кусков массива
	{
		double *tmp = new double[size1];
		for (int i = 0; i<size1; i++)
			tmp[i] = mas[i];
		double *mas2 = mas + size1;
		int a = 0;
		int b = 0;
		int i = 0;
		while ((a != size1) && (b != size2))
		{
			if (tmp[a] <= mas2[b])
			{
				mas[i] = tmp[a];
				a++;
			}
			else
			{
				mas[i] = mas2[b];
				b++;
			}
			i++;
		}
		if (a == size1)
			for (int j = b; j<size2; j++)
				mas[size1 + j] = mas2[j];
		else
			for (int j = a; j<size1; j++)
				mas[size2 + j] = tmp[j];
	}
public:
	ParallelSorter(double *_mas, int _size, int _portion) : //конструктор
		mas(_mas), size(_size), portion(_portion) {};
	
	task* execute() //объявление логической задачи
	{
		if (size <= portion) // если размер массива меньше или равен порции разделенной можду массивами
		{
			QuickSort(mas, size); //выполняем сортировку этого куска
		}
		else
		{
			ParallelSorter &sorter1 = *new (allocate_child())ParallelSorter(mas, size / 2, portion); //создаем объект класса для первого куска +1 таск
			ParallelSorter &sorter2 = *new (allocate_child())ParallelSorter(mas + size / 2, size / 2, portion); //для второго +1 таск
			set_ref_count(3); //числоо подчиненных задач +1, те 2+1=3
			spawn(sorter1); //добавляет задачу в очередь готовых к выполнению
			spawn_and_wait_for_all(sorter2); //добавляет задачу в очередь готовых к выполнению и ждет выполнения всех подчиненных задач
			MergeAndSort(size / 2, size - size / 2); //слияние двух отсортированных массивов
		}
		return NULL;
	}
};

void RootSorter(double *inp, int size, int nThreads) //функция, задающая корневой таск
{

	int portion = size / nThreads; //размер порции
	if (size%nThreads != 0)
		portion++;
	ParallelSorter& sorter = *new (task::allocate_root()) //корневой таск
		ParallelSorter(inp, size, portion); //для цельного массива
	task::spawn_root_and_wait(sorter); //добавляем в очередь и ждем выполнения подзадач
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

	RootSorter(arr, size, threads);

	time = omp_get_wtime() - time;

	printf("TBB time: %f\n", time);

	freopen(argv[3], "wb", stdout);
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(arr, sizeof(*arr), size, stdout);
	return 0;

}