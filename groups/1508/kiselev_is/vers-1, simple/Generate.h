#pragma once

#include <random> 
#include <ctime>
#include <fstream>

const int test_numb = 10;
const int max_size = 6;
const int max_value = 10;

void Generate() {
	double a, b;
	std::ofstream fout("generate.txt");
	srand(time(0));
	int size = 0;
	for (int i = 0; i < test_numb; i++) {
		size = rand() % max_size + 1;
		fout << size;
		for (int j = 0; j < size; j++) {									// параметры
			fout << " " << (static_cast<double>(rand()) / RAND_MAX * max_value);
		}
		a = (static_cast<double>(rand()) / RAND_MAX * max_value);
		b = (static_cast<double>(rand()) / RAND_MAX * max_value);
		if (a > b) fout << " " << b << " " << a << " ";
		else fout << " " << a << " " << b << " ";
		fout << 0.0001 << std::endl;
	}
	fout.close();
}
