#include "Grehem.h"
#include <random>
#include <stdio.h>

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

//Запуск через командную строку с вводом  1) номер теста, 2)имя файлы входных данных 3)имя файла выходных данных
int main(int argc, char * argv[])
{
	if (argc < 4)
	{
		std::cout << "ERROR: No file names" << std::endl;
		return 1;
	};
	//Алгоритм Грехема строит выпуклую оболочку только для 3 и более точек!
	int size_tests[] = { 3, 4, 5, 6, 8, 10, 12, 15, 20, 30, 40, 50, 100, 200, 300, 400, 500, 1000, 2000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000 };
	FILE* file;
	char* fileName = argv[2];
	file = fopen(fileName, "wb");
	int size = size_tests[atoi(argv[1])];

	fwrite(&size, sizeof(size), 1, file);
	dot* dotArr = new dot[size + 1];
	//Генерация массива точек
	genRandArray(dotArr, size);
	//Запись массива
	fwrite(dotArr, sizeof(*dotArr), size, file);
	fclose(file);

	fileName = argv[3];
	file = fopen(fileName, "wb");
	//Нахождение выпуклой оболочки
	std::pair<dot*, int> answer = grehemMethod(dotArr, size + 1);
	//Запись оболочки в файл
	fwrite(&answer.second, sizeof(int), 1, file);
	fwrite(answer.first, sizeof(*answer.first), answer.second, file);
	fclose(file);

	return 0;
}