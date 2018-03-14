#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cmath>
#include <string>
#include "point.h"

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

	// —ообщить тестирующей системе, что решение получило один из вердиктов verdict
	void write_verdict(verdict v) {
		write_type(ext_cls::VERDICT); fwrite(&v, sizeof (v), 1, bur);
	}
	
	// Ќаписать сообщение от checker'a пользователю.
	// Ќапример, что решение верное, или неверное.
	// »спользовать только латинские буквы и знаки препинани€
	void write_message(string str) {
		write_type(ext_cls::MESSAGE);
		int l = str.size();
		fwrite(&l, sizeof (l), 1, bur);
		fwrite (&str[0], sizeof (str[0]), l, bur);
	}

	// —ообщить тестирующей системе врем€ работы программы участника,
	// вычисленное с помощью before_code
	// x имеет размерность 100 нс = 10 ^ (-7) сек
	void write_time(long long x) {
		write_type(ext_cls::TIME);
		fwrite(&x, sizeof (x), 1, bur);
	}

	// —ообщить тестирующей системе, пам€ть затребованную программой участника
	void write_memory(unsigned long long x) {
		write_type(ext_cls::MEMORY);
		fwrite(&x, sizeof (x), 1, bur);
	}
} checker_result;

int main() {
	FILE * buo = fopen("points.out", "rb");
	FILE * bua = fopen("answer.txt", "rb");

	int res_size, ans_size;
	double res_time, ans_time;
	Point *res, *ans;

	fread(&res_time, sizeof(res_time), 1, buo);
	fread(&res_size, sizeof(res_size), 1, buo);

	fread(&ans_time, sizeof(ans_time), 1, bua);
	fread(&ans_size, sizeof(ans_size), 1, bua);

	if (ans_size != res_size) {
		checker_result.write_message("WA. Output is not correct.");
		checker_result.write_verdict(verdict::WA);
		checker_result.write_time(res_time * 1e7);

		fclose(bua);
		fclose(buo);

		return 0;
	}

	res = new Point[res_size];
	ans = new Point[res_size];

	fread(res, sizeof(*res), res_size, buo);
	fread(ans, sizeof(*res), res_size, bua);

	for (int i = 0; i < res_size; i++) {
		if (res[i].x != ans[i].x || res[i].y != ans[i].y) {
			checker_result.write_message("WA. Output is not correct.");
			checker_result.write_verdict(verdict::WA);
			checker_result.write_time(res_time * 1e7);

			fclose(bua);
			fclose(buo);

			return 0;
		}
	}

	checker_result.write_message("AC. Points are equal.");
	checker_result.write_verdict(verdict::AC);
	checker_result.write_time(res_time * 1e7);

	fclose(bua);
	fclose(buo);

	return 0;
}
