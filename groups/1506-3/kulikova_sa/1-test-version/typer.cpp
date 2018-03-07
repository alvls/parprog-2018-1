#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include "Sole.h"

//Текстовый файл преобразует в бинарный
//argv[1] - имя входного файла, argv[2] - имя выходного файла
int typer(int argc, char * argv[]) {
	if (argc != 3) {
		std::cout << "Некорректные данные" << std::endl;
		return 1;
	}

	FILE *in, *out;
	//char* number = new char[15];
	char* ptrEnd;
	Sole*S = new Sole();
	int N = 0;
	std::vector<int> array_data;
	in = fopen(argv[1], "rt");
	out = fopen(argv[2], "wb");
	if (in != nullptr) {
		while (fgets(number, 15, in) != nullptr)
			array_data.push_back(atoi(number));

		N = array_data.size();
		fwrite(&N, sizeof(N), 1, out);
		for (int i = 0; i < N; i++)
			fwrite(&array_data[i], sizeof(int), 1, out);
	}

	fclose(in);
	fclose(out);

	return 0;
}