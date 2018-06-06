#include "Grehem_Parallel.h"
#include <stdio.h>

//Запуск через командную строку с вводом 1) кол-во потоков, 2) имя файла с входными данными, 3)имя файлы выходных данных
int main(int argc, char * argv[])
{
	int nThreads = atoi(argv[1]);
	FILE * in_data = fopen(argv[2], "rb");
	//Считываем данные
	int size;
	fread(&size, sizeof(size), 1, in_data);
	dot* dotArray = new dot[size + 1];
	fread(dotArray, sizeof(*dotArray), size, in_data);
	fclose(in_data);

	//   Решаем методом Грэхема и записываем результат в файл
	//Нахождение выпуклой оболочки (tbb версия)
	std::pair<dot*, int> answer = grehemMethod_TBB(dotArray, size + 1, nThreads);
	//Запись оболочки в файл
	FILE * result_file = fopen(argv[3], "wb");
	fwrite(&answer.second, sizeof(int), 1, result_file);
	fwrite(answer.first, sizeof(*answer.first), answer.second, result_file);
	fclose(result_file);

	return 0;
}