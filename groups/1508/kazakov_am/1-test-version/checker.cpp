#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class Result {
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };

	Result() {
		result_file_.open("result.txt");
	}

	~Result() {
		result_file_.close();
	}

	void write_type(const ext_cls type) {
		result_file_ << type;
	}

	void write_verdict(const verdict verdict) {
		write_type(ext_cls::VERDICT);
		result_file_ << verdict;
	}

	void write_message(const std::string message) {
		write_type(ext_cls::MESSAGE);
		result_file_ << message;
	}

	void write_time(const long long time) {
		write_type(ext_cls::TIME);
		result_file_ << time;
	}

	void write_memory(const unsigned long long memory) {
		write_type(ext_cls::MEMORY);
		result_file_ << memory;
	}

private:
	std::ofstream result_file_;
};

Result checker_result;

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout
			<< "Checker\n"
			<< "Usage: [.exe name] [input file] [answer file]\n"
			<< "Result will be written in result.txt"
			<< std::endl;

		return 1;
	}

	std::ifstream input(argv[1], std::ifstream::binary);
	std::ifstream answer(argv[2], std::ifstream::binary);

	int input_size;
	int output_size;
	bool correct = true;

	input >> input_size;
	answer >> output_size;

	if (input_size == output_size) {
		double* inp_arr = new double[input_size];
		double* ans_arr = new double[input_size];

		input >> *inp_arr;
		answer >> *ans_arr;

		for (int i = 0; i < input_size; i++) {
			if (inp_arr[i] != ans_arr[i]) {
				correct = false;

				checker_result.write_message("WA: arrays are equal in sizes, but different by themselves");
				break;
			}
		}

		delete[] inp_arr;
		delete[] ans_arr;
	} else {
		correct = false;
		checker_result.write_message("WA: arrays are different in sizes");
	}

	if (correct) {
		checker_result.write_message("AC: arrays are equal");
		checker_result.write_verdict(verdict::AC);
	} else {
		checker_result.write_verdict(verdict::WA);
	}

	return 0;
}