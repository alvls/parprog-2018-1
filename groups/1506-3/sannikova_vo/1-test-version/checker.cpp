#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result {
private:
	FILE* bur;

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


int main(int argc, char * argv[])
{
	if (argc != 2 && argc!=3) {
		std::cout << "You input incorrect number of arguments. Input 'checker sort.bin' or 'sort1.bin sort2.bin' " << std::endl;
		return 1;
	}

	FILE * buo = fopen(argv[1], "rb");
	FILE * bua = nullptr;

	double time, time2; //sort time
	int n = 0, n2 = 0;   //number of elements in vector
	bool need_compare = false;

	if (argc == 3) {
		need_compare = true;
		bua = fopen(argv[2], "rb");
	}

	fread(&time, sizeof(time), 1, buo); //????????? ????? ??????????
	fread(&n, sizeof(n), 1, buo);

	if (need_compare == true) {
		fread(&time2, sizeof(time2), 1, bua);
		fread(&n2, sizeof(n2), 1, bua);
	}

	bool error = false;

	if (need_compare == true && n != n2) {
		checker_result.write_message("PE. Numbers of elements in the arrays are different.");
		checker_result.write_verdict(verdict::PE);
	}
	else {
		double prev = 0, cur = 0, ans_part;
		fread(&prev, sizeof(prev), 1, buo);
		if (need_compare == true) {
			fread(&ans_part, sizeof(ans_part), 1, bua);
			if (prev != ans_part) {
				error = true;
			}
				
		}
		if (error = false) {
			for (int i = 1; i < n; ++i) {
				fread(&cur, sizeof(cur), 1, buo);
				if (need_compare == true) {
					fread(&ans_part, sizeof(ans_part), 1, bua);
					if (cur != ans_part) {
						error = true;
						break;
					}
				}
				if (cur < prev) {
					error = true;
					break;
				}
				prev = cur;
			}
		}
		
		if (error == false) {
			checker_result.write_message("AC. Array is sorted correctly.");
			checker_result.write_verdict(verdict::AC);
		}
		else {
			checker_result.write_message("WA. Array sorting has an error.");
			checker_result.write_verdict(verdict::WA);
		}
		checker_result.write_time(static_cast<long long>(time * 1e7));
	}

	fclose(buo);
	if (need_compare == true)
		fclose(bua);
	return 0;
}