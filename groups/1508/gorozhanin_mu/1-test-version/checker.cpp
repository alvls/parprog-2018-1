#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

// Используется для взаимодействия с тестирующей системой
////////////////////////////////////////////////////////////////////////////////////////////

// Checker может устанавливать вот эти три вердикта:
//AC = Accepted = Решение выдаёт корректный результат на данном тесте
//WA = Wrong Answer = Решение выдаёт некорректный результат на данном тесте
//PE = Presentation Error = Ошибка формата выходных данных
// Остальные вердикты checker не может устанавливать
//NO = No verdict = Вердикт отсутствует
//CE = Compilation Error = Ошибка компиляции
//ML = Memory Limit Exceeded = Превышено ограничение по памяти
//TL = Time Limit Exceeded = Превышено ограничение по времени работы
//RE = Runtime Error = Ошибка времени исполнения программы
//IL = Idle Limit Exceeded = Превышено время простоя (бездействия) программы
//DE = Deadly Error = Ошибка тестирующей системы

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result {
private:
	FILE * bur;

public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };

	result(bool read = false) {
		if (read)
			bur = fopen("result.txt", "rt");
		else
			bur = fopen("result.txt", "wt");
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
	if (argc != 2) {
		cout << "You use the \"Checker\" to check new data. Enter the arguments in the correct format !!" << endl;
		return 1;
	}

	FILE * buo = fopen(argv[1], "rb");

	int res_size = 0;
	double res_time;

	fread(&res_time, sizeof(res_time), 1, buo);
	fread(&res_size, sizeof(res_size), 1, buo);
	//
	//Создаем флаг для проверки корректности решения.
	//Проверяем по очереди каждый элемент с правым относительно текущего до конца.
	//При хотя бы одном нарушении меняем флаг и выходим из цикла.
	//Проверка отдельным алгоритмом сортировки потребует больше времени и наличие исходных данных, а также больше памяти.
	//
	bool error = false;
	int previous = 0;
	int current = 0;
	fread(&previous, sizeof(previous), 1, buo);
	for (auto i = 1; i < res_size; i++) {
		fread(&current, sizeof(current), 1, buo);
		if (current < previous) {
			error = true;
			break;
		}
		previous = current;
	}
	if (error == false) {
		checker_result.write_message("AC. Array is sorted correctly.");
		checker_result.write_verdict(AC);
	}
	else {
		checker_result.write_message("WA. Array sorting has an error.");
		checker_result.write_verdict(WA);
	}
	checker_result.write_time(static_cast<long long>(res_time * 10000000));

	fclose(buo);
	return 0;
}

