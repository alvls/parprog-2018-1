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
											   // каждый запрос задаетс€ парой значений,
											   // а именно: левой(lbstack) и правой(ubstack)
											   // границами промежутка
	long stackpos = 1; // текуща€ позици€ стека
	long ppos; // середина массива

	double pivot; // опорный элемент
	//vector<double>::iterator temp;
	double temp;

	lbstack[1] = 0;
	ubstack[1] = distance(begin, end)-1;

	do {
		// ¬з€ть границы lb и ub текущего массива из стека.
		lb = lbstack[stackpos];
		ub = ubstack[stackpos];
		stackpos--;

		do {
			// Ўаг 1. –азделение по элементу pivot
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

			// —ейчас указатель i указывает на начало правого подмассива,
			// j - на конец левого (см. иллюстрацию выше), lb ? j ? i ? ub.
			// ¬озможен случай, когда указатель i или j выходит за границу массива

			// Ўаги 2, 3. ќтправл€ем большую часть в стек и двигаем lb,ub
			if (i < ppos) { // права€ часть больше
				if (i < ub) { // если в ней больше 1 элемента - нужно
					stackpos++; // сортировать, запрос в стек
					lbstack[stackpos] = i;
					ubstack[stackpos] = ub;
				}
				ub = j; // следующа€ итераци€ разделени€
						// будет работать с левой частью
			}
			else { // лева€ часть больше
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

//главна€ функци€ дл€ дальнейшей работы
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

//печать массива дл€ чека в мэйне
void printArray(double* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
