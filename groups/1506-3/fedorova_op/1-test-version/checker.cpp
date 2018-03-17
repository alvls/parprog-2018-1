
#include <cstdio>
#include <math.h>
#include <string>
using namespace std;

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result {
private: FILE * bur;
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
	result(bool read = false)
	{
		if (read)
			bur = fopen("result.txt", "r");
		else bur = fopen("result.txt", "w");
	}
	~result() { fclose(bur); }
	void write_type(ext_cls t) 
	{ 
		int whitch = int(t);
		switch (whitch)
		{
		case 1:
			fwrite(&" NO:", 4, 1, bur);
			break;
		case 2:
			fwrite(&" VERDICT:", 9, 1, bur);
			break;
		case 3:
			fwrite(&" MESSAGE:", 9, 1, bur);
			break;
		case 4:
			fwrite(&" TIME:", 6, 1, bur);
			break;
		case 5:
			fwrite(&" MEMORY:", 8, 1, bur);
			break;
		}
	}

	void write_verdict(verdict v)
	{ 
		write_type(ext_cls::VERDICT);
		int whitch = int(v);
		switch (whitch)
		{
		case 1:
			fwrite(&" NO", 3, 1, bur);
			break;
		case 2:
			fwrite(&" AC", 3, 1, bur);
			break;
		case 3:
			fwrite(&" WA", 3, 1, bur);
			break;
		}
	}

	void write_message(string str) 
	{
		write_type(ext_cls::MESSAGE); 
		int l = str.size(); 
		fwrite(&str[0], sizeof(str[0]), l, bur); 
	}

	void write_time(long long x)
	{
		write_type(ext_cls::TIME); 
		fwrite(&to_string(x), sizeof(x)-3, 1, bur);
	}
	void write_memory(unsigned long long x)
	{
		write_type(ext_cls::MEMORY);
		fwrite(&to_string(x), sizeof(x), 1, bur);
	}

}checker_result;

int main()
{
	FILE * bui = fopen("tests/1", "rb"); // параметры 
	FILE * buo = fopen("tests/1.ans", "rb"); // решение алгоритма Стронгина
	FILE * bua = fopen("etalon.out", "rb"); // элементраное решение перебором

	double parameter_r, epsilon, a, b; // параметр>1, останов по точности , интервал
	int funcNum;// номер функции
	fread(&funcNum, sizeof(funcNum), 1, bui);
	fread(&a, sizeof(a), 1, bui);
	fread(&b, sizeof(b), 1, bui);
	fread(&epsilon, sizeof(epsilon), 1, bui);
	fread(&parameter_r, sizeof(parameter_r), 1, bui);
	
	double ans_time, res_time, ans_x, ans_y, res_x, res_y;// время и результаты эталона и солвера

	fread(&res_x, sizeof(res_x), 1, buo);
	fread(&res_y, sizeof(res_y), 1, buo);
	fread(&res_time, sizeof(res_time), 1, buo);

	fread(&ans_x, sizeof(ans_x), 1, bua);
	fread(&ans_y, sizeof(ans_y), 1, bua);
	fread(&ans_time, sizeof(ans_time), 1, bua);

	double diff = abs(ans_x - res_x);

	if (diff <= 0.0015)
	{
		checker_result.write_verdict(verdict::AC);
		checker_result.write_message("Numbers are equal for function number " + to_string(funcNum) +
			". Difference: " + to_string(diff));
		
	}
	else 
	{ 
		checker_result.write_verdict(verdict::WA);
		checker_result.write_message("Output is not correct for function number " + to_string(funcNum) + 
			". Difference: " + to_string(diff));

	}

	// Записываем время в правильной размерности (интервалы по 100 нс = 10 ^ (-7) сек). 
	checker_result.write_time (res_time * 1e7); 

	fclose(bua); 
	fclose(buo); 

	return 0;
}