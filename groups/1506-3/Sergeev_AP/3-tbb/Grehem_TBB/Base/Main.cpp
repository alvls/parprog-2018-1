#include "Grehem_Parallel.h"
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <random>

void genRandArray(dot* arr, int size)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(-10000, 10000);
	for (int i = 0; i < size; i++)
	{
		arr[i].x = dis(gen);
		arr[i].y = dis(gen);
	}
}

///
void quickSort(dot* arr, int startInd, int endInd)
{
	if (startInd < endInd)
	{
		dot pivot = arr[startInd];
		int middleInd = startInd;
		for (auto i = startInd + 1; i < endInd; i++)
			if (arr[i] < pivot)
			{
				middleInd++;
				std::swap(arr[middleInd], arr[i]);
			}
		std::swap(arr[startInd], arr[middleInd]);
		quickSort(arr, startInd, middleInd);
		quickSort(arr, middleInd + 1, endInd);
	}
}

void quickSortSearchMin(dot* arr, int startInd, int endInd)
{
	if (startInd < endInd)
	{
		dot pivot = arr[startInd];
		int middleInd = startInd;
		for (auto i = startInd + 1; i < endInd; i++)
			if ((arr[i].x < pivot.x) || ((arr[i].x == pivot.x) && (arr[i].y < pivot.y)))
			{
				middleInd++;
				std::swap(arr[middleInd], arr[i]);
			}
		std::swap(arr[startInd], arr[middleInd]);
		quickSortSearchMin(arr, startInd, middleInd);
		quickSortSearchMin(arr, middleInd + 1, endInd);
	}
}


std::pair<dot*, int> grehemMethod(dot* dotArray, int size)
{
	quickSortSearchMin(dotArray, 0, size - 1);
	dot move = dotArray[0];
	for (auto i = 0; i < size - 1; i++)
		dotArray[i] = dotArray[i] - move;
	quickSort(dotArray, 1, size - 1);
	dotArray[size - 1] = dotArray[0];
	stack dotStack(size / 2);
	dot dotY, dotX;
	dotStack.push(dotArray[0]);
	dotStack.push(dotArray[1]);
	for (auto i = 2; i < size; i++)
	{
		while (true)
		{
			if (dotStack.getSize() > 1)
			{
				dotY = dotStack.pop();
				dotX = dotStack.get();
				if ((dotArray[i].x*(dotX.y - dotY.y) + dotArray[i].y*(dotY.x - dotX.x) + dotX.x*dotY.y - dotX.y*dotY.x) > 0)
				{
					dotStack.push(dotY);
					dotStack.push(dotArray[i]);
					break;
				}
				else
				{
					if (dotStack.getSize() == 1)
					{
						dotStack.push(dotArray[i]);
						break;
					}
				}
			}
		}
	}
	dot* resultArray = dotStack.getArray();
	for (auto i = 0; i < dotStack.getSize(); i++)
	{
		resultArray[i] = resultArray[i] + move;
	}
	return std::make_pair(resultArray, dotStack.getSize());
}
///

int main()
{
	setlocale(LC_ALL, "Russian");
	int size = 100;
	dot* arr = new dot[size + 1];
	genRandArray(arr, size);
	///
	dot* parallelArr = new dot[size + 1];
	for (auto i = 0; i < size; i++)
		parallelArr[i] = arr[i];
	///
	int num_threads = 2;

	auto start_TBB = std::chrono::high_resolution_clock::now();
	std::pair<dot*, int> answer_TBB = grehemMethod_TBB(arr, size + 1, num_threads);
	auto end_TBB = std::chrono::high_resolution_clock::now();
	std::cout << " Время выполнения TBB " << std::chrono::duration_cast<std::chrono::microseconds>(end_TBB - start_TBB).count() << " (микросекунды)" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();
	std::pair<dot*, int> answer = grehemMethod(parallelArr, size + 1);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << " Время выполнения " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " (микросекунды)" << std::endl;

	if (answer.second != answer_TBB.second)
		std::cout << "Параллельный результат неверен: количество точек в выпуклых оболочках не совпадают" << std::endl;

	for (int i = 0; i < answer.second; i++)
	{
		if (answer.first[i] != answer_TBB.first[i])
		{
			std::cout << "Параллельный результат неверен: выпуклые оболчки не совпадают" << std::endl;
			return 1;
		}
	}

	std::cout << "Выпуклые оболочки совпали" << std::endl;

	return 0;
}