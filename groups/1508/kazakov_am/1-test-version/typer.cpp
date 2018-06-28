#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout
			<< "Typer\n"
			<< "Usage: [.exe name] [input file] [output file]"
			<< std::endl;

		return 1;
	}

	std::ifstream input(argv[1]);
	FILE* output = fopen(argv[2], "wb");

	double time;
	int arr_size;
	double* arr;

	input >> time >> arr_size;

	arr = new double[arr_size];

	for (int i = 0; i < arr_size; i++) {
		input >> arr[i];
	}

	fwrite(&time, sizeof(time), 1, output);
	fwrite(&arr_size, sizeof(arr_size), 1, output);
	fwrite(arr, sizeof(arr), arr_size, output);

	fclose(output);
	input.close();
	delete[] arr;

	return 0;
}