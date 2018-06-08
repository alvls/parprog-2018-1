#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>

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
	if (argc != 2) return 0;

	FILE * buo = fopen(argv[1], "rb");

	int res_n;
	double res_time;

	fread(&res_time, sizeof(res_time), 1, buo);
	fread(&res_n, sizeof(res_n), 1, buo);

	bool error = false;
	double lower_value = 0, more_value = 0;
	fread(&lower_value, sizeof(lower_value), 1, buo);
	for (int i = 1; i < res_n; i++) {
		fread(&more_value, sizeof(more_value), 1, buo);
		if (lower_value < more_value) {
			error = true;
			break;
		}
		lower_value = more_value;
	}
	if (error) {
		checker_result.write_message("WA. Output is not correct.");
		checker_result.write_verdict(verdict::WA);
	}
	else {
		checker_result.write_message("AC. Numbers are equal.");
		checker_result.write_verdict(verdict::AC);
	}
	checker_result.write_time(res_time * 1e7);
	fclose(buo);

	return 0;
}