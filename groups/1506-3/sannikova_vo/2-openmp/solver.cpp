#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <chrono>
#include <iostream>
#include <random>
#include "math.h"
#define MAXSTACK 2048
using namespace std;

void qSort_NO_recursion(vector<double>::iterator begin, vector<double>::iterator end)
{
	long i, j; // указатели, участвующие в разделении
	long lb, ub; // границы сортируемого в цикле фрагмента

	long lbstack[MAXSTACK], ubstack[MAXSTACK]; // стек запросов
											   // каждый запрос задается парой значений,
											   // а именно: левой(lbstack) и правой(ubstack)
											   // границами промежутка
	long stackpos = 1; // текущая позиция стека
	long ppos; // середина массива

	double pivot; // опорный элемент
	//vector<double>::iterator temp;
	double temp;

	lbstack[1] = 0;
	ubstack[1] = distance(begin, end)-1;

	do {
		// Взять границы lb и ub текущего массива из стека.
		lb = lbstack[stackpos];
		ub = ubstack[stackpos];
		stackpos--;

		do {
			// Шаг 1. Разделение по элементу pivot
			ppos = (lb + ub) >> 1; //середина 
			i = lb; 
			j = ub; 
			pivot = *(begin + ppos); // vec[ppos];
			do {
				while (/*a[i]*/ *(begin+i) < pivot) 
					i++;
				while (pivot < /*a[j]*/ *(begin+j)) 
					j--;
				if (i <= j) {
					temp = *(begin + i); // a[i];
					*(begin + i) = *(begin + j); //a[i] = a[j]; 
					*(begin + j) = temp; //a[j] = temp;
					i++; 
					j--;
				}
			} while (i <= j);

			// Сейчас указатель i указывает на начало правого подмассива,
			// j - на конец левого (см. иллюстрацию выше), lb ? j ? i ? ub.
			// Возможен случай, когда указатель i или j выходит за границу массива

			// Шаги 2, 3. Отправляем большую часть в стек и двигаем lb,ub
			if (i < ppos) { // правая часть больше
				if (i < ub) { // если в ней больше 1 элемента - нужно
					stackpos++; // сортировать, запрос в стек
					lbstack[stackpos] = i;
					ubstack[stackpos] = ub;
				}
				ub = j; // следующая итерация разделения
						// будет работать с левой частью
			}
			else { // левая часть больше
				if (j > lb) {
					stackpos++;
					lbstack[stackpos] = lb;
					ubstack[stackpos] = j;
				}
				lb = i;
			}
		} while (lb < ub); // пока в меньшей части более 1 элемента
	} while (stackpos != 0); // пока есть запросы в стеке
}

//главная функция для дальнейшей работы
void qSort(vector<double>::iterator begin, vector<double>::iterator end)
{
	int first = 0;
	int length = distance(begin, end);
	int last = distance(begin, end) - 1;
	double elem = *(begin + ((first + last) >> 1));

	do {
		while (*(begin + first) < elem)
			first++;
		while (*(begin + last) > elem)
			last--;

		if (first <= last) {
			double temp = *(begin + first);
			*(begin + first) = *(begin + last);
			*(begin + last) = temp;
			first++;
			last--;
		}
	} while (first <= last);


	if (last > 0)
		qSort(begin, begin + last + 1);
	if (first < distance(begin, end))
		qSort(begin + first, end);
}

//обертка
void qSort(vector <double>* vec) {
	vector<double>::iterator begin = vec->begin();
	vector<double>::iterator end = vec->end();
	qSort(begin, end);
}

void qSort_array_recursion(double* arr, int size)
{
	int first = 0;
	int last = size - 1;
	double elem = arr[size / 2];

	do {
		while (arr[first] < elem)
			first++;
		while (arr[last] > elem)
			last--;

		if (first <= last) {
			double tmp = arr[first];
			arr[first] = arr[last];
			arr[last] = tmp;
			first++;
			last--;
		}
	} while (first <= last);


	if (last > 0)
		qSort_array_recursion(arr, last + 1);
	if (first < size)
		qSort_array_recursion(&arr[first], size - first);
}

//печать массива для чека в мэйне
void printArray(double* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int Partition(double items[], int first, int last, double pivot) { //разделение по номеру элемента, слева будут все элементы < pivot
	int j = first - 1;
	for (int i = first; i <= last; ++i) {
		if (items[i] < pivot) {
			std::swap(items[++j], items[i]);
		}
	}
	return j; //позиция pivot
}

int PartitionByIndex(double items[], int first, int last, int index) { //разделение по индексу
	std::swap(items[index], items[last]);
	int i = 1 + Partition(items, first, last, items[last]);
	std::swap(items[i], items[last]);
	return i; //позиция на которой стоит элемент который стоял на позиции index
}

void Select(double items[], int first, int last, int index) { //выбор участка массива
	int i = PartitionByIndex(items, first, last, (first + last) / 2); //выбираем новую позицию медианы
	if (i > index) { //если новая позиция медианы больше индекса
		Select(items, first, i - 1, index); //то выбираем левую часть до нового индекса
	}
	else if (i < index) {
		Select(items, i + 1, last, index); //выбираем правую часть после нового индекса
	}
}

#pragma once
#include <iostream>

void QuickSort(double items[], int size/*int first, int last*/) { //быстрая рекурсивная сортировка
	int i = PartitionByIndex(items, 0, size - 1, (size - 1) / 2);
	if (i - 1 > 0/*first*/) {
		QuickSort(items, i /*first, i - 1*/);
	}
	if (i + 1 < size - 1/*last*/) {
		QuickSort(&items[i + 1], size - i - 1 /* i + 1, last*/);
	}
}

#pragma once
#include <iostream>
#include <algorithm>
#include <cmath>
#include <omp.h>
using namespace std;


void QuickSort_OpenMP(double items[], int size /*int first, int last*/, int deep, int maxDeep) { //0, 8
	if (deep >= maxDeep) { //если текушаю глубина больше максимальной
		QuickSort(items, size /*first, last*/); //просто выполняем сортировку
	}
	else {
		int i = /*(first + last)*/ (size - 1) / 2; //иначе мы выбираем серединный элемент
		Select(items, 0, size - 1, i);
		//Select(items, size/*first, last*/, i); //и выполняем выборку

#pragma omp parallel
		{
#pragma omp sections nowait
			{
#pragma omp section
				if (i - 1 > 0/*first*/) {
					QuickSort_OpenMP(items, i/*first, i - 1*/, deep + 1, maxDeep);
				}
#pragma omp section
				if (i + 1 < size - 1/*last*/) {
					QuickSort_OpenMP(&items[i + 1], size - i - 1/*i + 1, last*/, deep + 1, maxDeep);
				}
			}
		}
	}
}

void QuickSort_OpenMP(double items[], int size /*int first, int last*/) {
	int maxDeep = (int)(ceil(log((double)omp_get_num_procs()) / log(2.0))); //максимальная глубина рекурсиии если 8 потоков то 3
	QuickSort_OpenMP(items, size /*first, last*/, 0, maxDeep);
}
