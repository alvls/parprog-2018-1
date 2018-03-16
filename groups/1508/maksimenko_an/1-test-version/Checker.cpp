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
	if (argc != 3)
		return 0;

	FILE * buo = fopen(argv[1], "rb");
	FILE * bua = fopen(argv[2], "rb");

	int res_n, ans_n;
	double res_time, ans_time;

	fread(&res_time, sizeof(res_time), 1, buo);
	fread(&res_n, sizeof(res_n), 1, buo);

	fread(&ans_time, sizeof(ans_time), 1, bua);
	fread(&ans_n, sizeof(ans_n), 1, bua);

	if (res_n != ans_n) {
		checker_result.write_message("PE. Number of elements in the array is different.");
		checker_result.write_verdict(verdict::PE);
	}
	else {
		bool error = false;
		double ans_value = 0, res_value = 0;
		for (int i = 0; i < ans_n; i++) {
			fread(&res_value, sizeof(res_value), 1, buo);
			fread(&ans_value, sizeof(ans_value), 1, bua);
			if (res_value != ans_value) {
				error = true;
				break;
			}
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
	}
	fclose(bua);
	fclose(buo);

	return 0;
}