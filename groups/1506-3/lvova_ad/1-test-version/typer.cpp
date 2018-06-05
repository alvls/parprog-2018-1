#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

//Текстовый файл преобразует в бинарный

int main(int argc, char * argv[]) 
{
	int size;
	std::ifstream input_file("../massiv.txt", std::ios::in);
	
	if (!input_file.is_open()) 
	{
		std::cout << "File can not open to read" << std::endl;
		return 1;
	}

	input_file >> size;

	if (size < 1) 
	{
		std::cout << "Incorrect size of array" << std::endl;
		return 2;
	}

	FILE * output_file = fopen("../massiv.in", "wb");

	if (output_file == nullptr)
	{
		std::cout << "File can not open to write" << std::endl;
		return 3;
	}

	fwrite(&size, sizeof(size), 1, output_file);
	double * A = new double[size];

	for (int i = 0; i < size; i++) 
	{
		input_file >> A[i];
		fwrite(&A[i], sizeof(A[i]), 1, output_file);
	}

	input_file.close();
	fclose(output_file);

	return 0;
}
