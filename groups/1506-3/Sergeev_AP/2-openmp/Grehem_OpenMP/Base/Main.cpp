#include "Grehem_Parallel.h"
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <random>

void genRandArray(dot* arr, int size)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 10);
	for (int i = 0; i < size; i++)
	{
		arr[i].x = dis(gen);
		arr[i].y = dis(gen);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int size = 20;
	dot* arr = new dot[size + 1];
	genRandArray(arr, size);
	int num_threads = 8;

	std::cout << "Сгенерированный массив" << std::endl;
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i].x << " " << arr[i].y << std::endl;
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

	return 0;
}