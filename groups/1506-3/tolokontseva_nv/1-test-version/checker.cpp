
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio> 
#include <cmath> 
#include <string>
using namespace std;
/* Checker может устанавливать вот эти три вердикта: 
AC = Accepted = Решение выдаёт корректный результат на данном тесте
WA = Wrong Answer = Решение выдаёт некорректный результат на данном тесте 
PE = Presentation Error = Ошибка формата выходных данных
*/
enum verdict { AC, WA, PE };
class result {
private: FILE * bur;
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
	result(bool read = false) {
		if (read) {
			bur = fopen("result.txt", "r");
		}
		else {
			bur = fopen("result.txt", "w");
		}
	}
	~result() { fclose(bur); }
	void write_type(ext_cls t) {
		fwrite(&t, sizeof(t), 1, bur);
	}
	// Сообщить тестирующей системе, что решение получило один из вердиктов verdict
	void write_verdict(verdict v) { 
		write_type(ext_cls::VERDICT);
		fwrite(&v, sizeof(v), 1, bur);
	}
	// Написать сообщение от checker'a пользователю. 
	// Например, что решение верное, или неверное. 
	// Использовать только латинские буквы и знаки препинания
	void write_message(string str) {
		write_type(ext_cls::MESSAGE);
		size_t l = str.size();
		fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);
	}
	// Сообщить тестирующей системе время работы программы участника, 
	// вычисленное с помощью before_code 
	// x имеет размерность 100 нс = 10 ^ (-7) сек 
	void write_time(long long x) { 
		write_type(ext_cls::TIME); 
		fprintf(bur, " %lld\n", x);
	}
	// Сообщить тестирующей системе, память затребованную программой участника 
	void write_memory(unsigned long long x) {
		write_type(ext_cls::MEMORY);
		fwrite(&x, sizeof(x), 1, bur);
	}
} checker_result;

int main(int argc, char* argv[]) {
	string f_in_s = "arr.in",
		f_out_s = "arr.out",
		f_ans_s = "arr.ans";
	char f_in[100], f_out[100], f_ans[100];
	if (argc > 1) {
		if (argc != 4) {
			printf("Expected either 0 or 3 args: <input file name> <output file name> <answer file name>");
		}
		f_in_s = string(argv[1]);
		f_out_s = string(argv[2]);
		f_ans_s = string(argv[3]);
	}
	strcpy(f_in, f_in_s.c_str());
	strcpy(f_out, f_out_s.c_str());
	strcpy(f_ans, f_ans_s.c_str());

	// Открываем файл входных данных, файл выходных данных и файл с эталоном
	FILE * file_in = fopen(f_in, "rb");
	FILE * file_out = fopen(f_out, "rb");
	FILE * file_ans = fopen(f_ans, "rb");
	int n;
	// Считываем размерность массива 
	fread(&n, sizeof(n), 1, file_in);
	// Выделяем память для массива отсортированного алгоритмом из библиотеки и нашим алгоритмом 
	double *ans = new double[n],
		*res = new double[n]; 
	double ans_time, res_time;
	// Считываем время работы  нашего алгоритма и получившийся в результате массив
	fread(&n, sizeof(n), 1, file_out);
	fread(&res_time, sizeof (res_time), 1, file_out); 
	fread(res, sizeof (*res), n, file_out);
	// Считываем время работы стандартного алгоритма и получившийся в результате массив
	fread(&n, sizeof(n), 1, file_ans);
	fread(&ans_time, sizeof (ans_time), 1, file_ans); 
	fread(ans, sizeof (*ans), n, file_ans);

	//т.к. никаких вычислений не производилось, никакой погрешности быть не должго
	//проверяем, что решение корректно
	bool isCorrect = true;
	for (int i = 0; i < n; i++) {
		if (res[i] != ans[i]) {
			isCorrect = false;
			break;
		}
	}
	if (isCorrect) { 
		checker_result.write_message ("AC. Arrays are identic.");
		checker_result.write_verdict (verdict::AC); 
	} else { 
		checker_result.write_message ("WA. Output is not correct.");
		checker_result.write_verdict (verdict::WA);
	}

	// Записываем время в правильной размерности (интервалы по 100 нс = 10 ^ (-7) сек). 
	long long time;
	time = (long long)(res_time);
	checker_result.write_time(time);

	fclose(file_ans);
	fclose(file_out);
	fclose(file_in);
	return 0;
}