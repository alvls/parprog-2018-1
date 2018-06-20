#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

int main(int argc, char** argv) {
	const int max_number_of_tests = 46;

	if (argc < 3) {
		std::cout
			<< "Generator\n"
			<< "Usage: [.exe name] [order] [test set number 1] [test set number 2] ...\n"
			<< "Order of elements: 0 - random, any int > 0 - ascending, any int < 0 - descending\n"
			<< "NOTE: set numbers count from 0 to " << max_number_of_tests - 1
			<< "; you can type as many test set numbers as you want; "
			<< "if the current set doesn't exists nothing will happen."
			<< std::endl;

		return 1;
	}

	int number_of_tests[max_number_of_tests];

	for (int i = 0; i < max_number_of_tests / 2; i++) {
		// gonna be 1, 1, 2, 3, 4, 5, 8, 9, 16, 17, 32, 33, 64, 65, 128, 129,...
		number_of_tests[2 * i] = 1 << i;
		number_of_tests[2 * i + 1] = (1 << i) + 1;
	}

	const int order = atoi(argv[1]);

	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> distribution(-1e4, 1e4);

	std::set<int> active_tests;

	for (int i = 2; i < argc; i++) {
		const int curr_set_number = atoi(argv[i]);

		if (curr_set_number < 0
			|| curr_set_number > max_number_of_tests - 1) {
			continue;
		}

		active_tests.insert(curr_set_number);
	}


	for (auto it = active_tests.begin(); it != active_tests.end(); ++it) {
		char name[32];
		_itoa(*it, name, 10);

		// first arguments means just *it in string form
		FILE* f = fopen(name, "wb");

		const int curr_tests_num = number_of_tests[*it];

		// double is for the execution time, nothing here now
		fwrite(&curr_tests_num, sizeof(double), 1, f);
		fwrite(&curr_tests_num, sizeof(curr_tests_num), 1, f);

		std::vector<double> temp(curr_tests_num);

		for (auto it_temp = temp.begin(); it_temp != temp.end(); ++it_temp) {
			*it_temp = distribution(generator);
		}

		if (order) {
			std::sort(
				temp.begin(),
				temp.end(),
				[order](const int a, const int b) -> bool { return order > 0 ? a < b : a > b; }
			);
		}

		fwrite(temp.data(), sizeof(temp.data()), curr_tests_num, f);

		fclose(f);
	}

	return 0;
}