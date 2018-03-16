//Грибов П.Г. 381506-3. Поразрядная сортировка с простым слиянием. Последовательная версия. MyRadixSort_Lin.h
#pragma once

#include <queue>
#include <vector>
#include <algorithm>

using std::queue;
using std::vector;

//функция получения требуемого разряда числа
int get_dig(int num, int dig_num);

//поразрядная сортировка
void radix_sort(vector<int>& vec);