#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout
			<< "Viewer\n"
			<< "Usage: [.exe name] [input file] [output file]"
			<< std::endl;

		return 1;
	}

	std::ifstream input(argv[1], std::ifstream::binary);
	std::ofstream output(argv[2]);

	int arr_size;
	double* arr;

	input >> arr_size;

	arr = new double[arr_size];

	for (int i = 0; i < arr_size; i++) {
		input >> arr[i];
	}

	output << arr_size;

	for (int i = 0; i < arr_size; i++) {
		output << arr[i];
		
		std::cout << arr[i];

		if (i != arr_size - 1) {
			std::cout << " ";
		}
	}

	std::cout << std::endl;

	delete[] arr;

	return 0;
}