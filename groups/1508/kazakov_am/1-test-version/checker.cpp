#define _CRT_SECURE_NO_WARNINGS

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
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME };

	Result() {
		result_file_.open("result.txt");
	}

	~Result() {
		result_file_.close();
	}

	void write_verdict(const verdict verdict) {
		write_type(ext_cls::VERDICT);
		result_file_ << verdict << " ";
	}

	void write_message(const std::string message) {
		write_type(ext_cls::MESSAGE);
		result_file_ << message << " ";
	}

	void write_time(const long long time) {
		write_type(ext_cls::TIME);
		result_file_ << time << " ";
	}

private:
	std::ofstream result_file_;

	void write_type(const ext_cls type) {
		result_file_ << type << " ";
	}
};

Result checker_result;

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout
			<< "Checker\n"
			<< "Usage: [.exe name] [input file] [answer file]\n"
			<< "Result will be written in result.txt"
			<< std::endl;

		return 1;
	}

	FILE* input = fopen(argv[1], "rb");
	FILE* answer = fopen(argv[2], "rb");

	double input_time;
	double answer_time;
	int input_size;
	int answer_size;
	bool correct = true;

	fread(&input_time, sizeof(input_time), 1, input);
	fread(&input_size, sizeof(input_size), 1, input);
	fread(&answer_time, sizeof(answer_time), 1, answer);
	fread(&answer_size, sizeof(answer_size), 1, answer);

	if (input_size == answer_size) {
		double* inp_arr = new double[input_size];
		double* ans_arr = new double[input_size];

		fread(inp_arr, sizeof(inp_arr), input_size, input);
		fread(ans_arr, sizeof(ans_arr), input_size, answer);

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

	checker_result.write_time(answer_time);

	fclose(input);
	fclose(answer);

	return 0;
}