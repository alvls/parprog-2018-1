#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout
			<< "Viewer\n"
			<< "Usage: [.exe name] [input file] [output file]"
			<< std::endl;

		return 1;
	}

	FILE* input = fopen(argv[1], "rb");
	std::ofstream output(argv[2]);

	double time; 
	int arr_size;
	double* arr;

	fread(&time, sizeof(time), 1, input);
	fread(&arr_size, sizeof(arr_size), 1, input);

	arr = new double[arr_size];

	fread(arr, sizeof(arr), arr_size, input);

	output << time << "\n" << arr_size << "\n";
	std::cout << time << "\n" << arr_size;

	/*for (int i = 0; i < arr_size; i++) {
		output << " " << arr[i];
	}*/

	output.close();
	fclose(input);
	delete[] arr;

	return 0;
}