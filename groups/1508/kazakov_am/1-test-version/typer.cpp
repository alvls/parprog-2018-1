#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout
			<< "Typer\n"
			<< "Usage: [.exe name] [input file] [output file]"
			<< std::endl;

		return 1;
	}

	std::ifstream input(argv[1]);
	std::ofstream output(argv[2], std::ofstream::binary);

	int arr_size;
	double* arr;

	input >> arr_size;

	arr = new double[arr_size];

	input >> *arr;

	/*for (int i = 0; i < arr_size; i++) {
		input >> arr[i];
	}*/

	output << arr_size;

	output << *arr;

	/*for (int i = 0; i < arr_size; i++) {
		output << arr[i];
	}*/

	delete[] arr;

	//FILE* input = fopen(argv[1], "rt");
	//FILE* output = fopen(argv[2], "wb");

	//size_t arr_size;
	//double* arr;
	//double curr_number[1];

	//fgets(&arr_size, 1, input);

	//arr 

	//while (fscanf(input, "%lf ", curr_number) > 0) {
	//	arr_size++;

	//}

	return 0;
}