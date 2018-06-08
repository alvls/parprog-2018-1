#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <string> 
#include <iostream>
#include <vector>

using namespace std;

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result {
private:
	FILE * bur;
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };

	result(bool read = false) {
		if (read)
			bur = fopen("result.txt", "r");
		else
			bur = fopen("result.txt", "w");
	}

	~result() {
		fclose(bur);
	}

	void write_type(ext_cls t) {
		fwrite(&t, sizeof(t), 1, bur);
	}

	void write_verdict(verdict v) {
		write_type(ext_cls::VERDICT);
		fwrite(&v, sizeof(v), 1, bur);
	}


	void write_message(string str) {
		write_type(ext_cls::MESSAGE);
		int l = str.size();
		fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);
	}


	void write_time(long long x) {
		write_type(ext_cls::TIME);
		fwrite(&x, sizeof(x), 1, bur);
	}


	void write_memory(unsigned long long x) {
		write_type(ext_cls::MEMORY);
		fwrite(&x, sizeof(x), 1, bur);
	}
} checker_result;


int main(int argc, char * argv[]) {

	if (argc != 3) {
		cout << "Use 'checker <output file> <answer file>'" << endl;
		return 1;
	}

	FILE * buo = fopen(argv[1], "rb");
	FILE * bua = fopen(argv[2], "rb");
	vector<int> out, res;
	double res_time;
	double tmp;
	int size;
	int number1;
	int number2;
	bool error = false;
	fread(&res_time, sizeof(res_time), 1, buo);
	fread(&tmp, sizeof(res_time), 1, bua);
	fread(&size, sizeof(size), 1, buo);
	fread(&size, sizeof(size), 1, bua);
	while (fread(&number1, sizeof(number1), 1, buo) && fread(&number2, sizeof(number2), 1, bua)) {
		if (number1 != number2) {
			error = true;
			break;
		}
	}

	if (!error) {
		checker_result.write_message("AC. Numbers are equal.");
		checker_result.write_verdict(verdict::AC);
	}
	else {
		checker_result.write_message("WA. Output is not correct.");
		checker_result.write_verdict(verdict::WA);
	}

	checker_result.write_time(static_cast<long long>(res_time * 1e7));
	fclose(bua);
	fclose(buo);
	return 0;
}