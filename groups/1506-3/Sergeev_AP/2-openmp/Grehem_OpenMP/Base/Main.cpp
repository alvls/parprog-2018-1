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

std::pair<dot*, int> grehemMethod(dot* dotArray, int size)
{
	searchMinElement(dotArray, size - 1, 8);
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


int main()
{
	setlocale(LC_ALL, "Russian");
	int size = 40;
	dot* arr = new dot[size + 1];
	genRandArray(arr, size);
	int num_threads = 8;
	omp_set_num_threads(num_threads);

	std::cout << "Сгенерированный массив" << std::endl;

	dot* arr2 = new dot[size + 1];//

	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i].x << " " << arr[i].y << std::endl;
		arr2[i] = arr[i];//
	}


	auto start = std::chrono::high_resolution_clock::now();
	std::pair<dot*, int> answer = grehemMethod_OpenMP(arr, size + 1, num_threads);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << " Время выполнения " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " (микросекунды)" << std::endl;

	std::cout << "Выпуклая оболочка" << std::endl;
	for (int i = 0; i < answer.second; i++)
	{
		std::cout << answer.first[i].x << " " << answer.first[i].y << std::endl;
	}

	start = std::chrono::high_resolution_clock::now();
	std::pair<dot*, int> answer2 = grehemMethod(arr2, size + 1);
	end = std::chrono::high_resolution_clock::now();
	std::cout << " Время выполнения " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " (микросекунды)" << std::endl;

	std::cout << "Выпуклая оболочка" << std::endl;
	for (int i = 0; i < answer2.second; i++)
	{
		std::cout << answer2.first[i].x << " " << answer2.first[i].y << std::endl;
	}

	if (answer.second != answer2.second)
		std::cout << "ACHTUNG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

	return 0;
}