#include <random>
#include <chrono>
#include <iostream>
#include "Grehem.h"

void genRandArray(dot* arr, int size)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(-100000, 100000);
	for (int i = 0; i < size; i++)
	{
		arr[i].x = dis(gen);
		arr[i].y = dis(gen);
	}
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "Russian");
	int size = 50;
	dot* arr = new dot[size + 1];
	genRandArray(arr, size);

	std::cout << "Сгенерированный массив" << std::endl;
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i].x << " " << arr[i].y << std::endl;
	}

	auto start = std::chrono::high_resolution_clock::now();
	std::pair<dot*, int> answer = grehemMethod(arr, size + 1);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << " Время выполнения " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " (микросекунды)" << std::endl;

	std::cout << "Выпуклая оболочка" << std::endl;
	for (int i = 0; i < answer.second; i++)
	{
		std::cout << answer.first[i].x << " " << answer.first[i].y << std::endl;
	}

	return 0;
}