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
	if (argc != 3) {
		std::cout << "Use 'checker [output file] [answer file]'" << std::endl;
		return 1;
	}

	FILE * buo = fopen(argv[1], "rb"); 
	FILE * bua = fopen(argv[2], "rb");

	int ans_n = 0, res_n = 0;
	double ans_time, res_time;

	// выходной файл
	fread(&res_time, sizeof(res_time), 1, buo);
	fread(&res_n, sizeof(res_n), 1, buo);

	// файл с верным результатом
	fread(&ans_time, sizeof(ans_time), 1, bua);
	fread(&ans_n, sizeof(ans_n), 1, bua);

	if (ans_n != res_n) {
		checker_result.write_message("PE. Number of elements in the array is different.");
		checker_result.write_verdict(verdict::PE);
	}
	else {
		bool error = false;
		int ans_part = 0, res_part = 0;

		for (int i = 0; i < res_n; ++i) {
			fread(&res_part, sizeof(res_part), 1, buo);
			fread(&ans_part, sizeof(ans_part), 1, bua);
			if (res_part != ans_part) {
				error = true;
				break;
			}
		}

		if (error == false) {
			checker_result.write_message("AC. Array is sorted correctly.");
			checker_result.write_verdict(verdict::AC);
		}
		else {
			checker_result.write_message("WA. Array sorting has an error.");
			checker_result.write_verdict (verdict::WA);
		}
		checker_result.write_time(static_cast<long long>(res_time * 1e7));
	}

	fclose(bua);
	fclose(buo);
	return 0;
}