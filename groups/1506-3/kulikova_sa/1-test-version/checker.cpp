#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <cmath> 
#include <string>
#include "Sole.h"

// Используется для взаимодействия с тестирующей системой
/* 
// Checker может устанавливать вот эти три вердикта: 
AC = Accepted = Решение выдаёт корректный результат на данном тесте 
WA = Wrong Answer = Решение выдаёт некорректный результат на данном тесте 
PE = Presentation Error = Ошибка формата выходных данных
// Остальные вердикты checker не может устанавливать 
NO = No verdict = Вердикт отсутствует 
CE = Compilation Error = Ошибка компиляции 
ML = Memory Limit Exceeded = Превышено ограничение по памяти 
TL = Time Limit Exceeded = Превышено ограничение по времени работы 
RE = Runtime Error = Ошибка времени исполнения программы 
IL = Idle Limit Exceeded = Превышено время простоя (бездействия) программы 
DE = Deadly Error = Ошибка тестирующей системы 
*/

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

	// Сообщить тестирующей системе, что решение получило один из вердиктов verdict 
	void write_verdict(verdict v) { 
		write_type(ext_cls::VERDICT); 
		fwrite(&v, sizeof (v), 1, bur); 
	}

	// Написать сообщение от checker'a пользователю. 
	// Например, что решение верное, или неверное. 
	// Использовать только латинские буквы и знаки препинания 
	void write_message(std::string str) { 
		write_type(ext_cls::MESSAGE); 
		int l = str.size (); 
		fwrite(&l, sizeof (l), 1, bur); 
		fwrite (&str[0], sizeof (str[0]), l, bur); 
	}

	// Сообщить тестирующей системе время работы программы участника, 
	// вычисленное с помощью before_code 
	// x имеет размерность 100 нс = 10 ^ (-7) сек 
	void write_time(long long x) { 
		write_type(ext_cls::TIME); 
		fwrite(&x, sizeof (x), 1, bur); 
	}

	// Сообщить тестирующей системе, память затребованную программой участника 
	void write_memory(unsigned long long x) { 
		write_type(ext_cls::MEMORY); 
		fwrite(&x, sizeof (x), 1, bur); 
	} 

} checker_result;


//argv[1] - имя файла участника, argv[2] - имя файла жюри
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");//Корректное отображение Кириллицы

	if (argc != 3) {
		std::cout << "Некорректные данные" << std::endl;
		return 1;
	}

	// Открываем файл выходных данных и ответ участника  
	FILE * buo = fopen(argv[1], "rb"); 
	FILE * bua = fopen(argv[2], "rb");

	if (buo == nullptr) {
		std::cout << "Файл участника не может быть открыт" << std::endl;
		return 2;
	}

	if (bua == nullptr) {
		std::cout << "Файл жюри не может быть открыт" << std::endl;
		return 3;
	}

	// Время работы участника
	double res_time;

	// Считываем время работы программы участника
	fread(&res_time, sizeof(res_time), 1, buo);

	int n; 
	// Считываем размерность матриц 
	fread(&n, sizeof (n), 1, buo);

	if (n < 1) {
		std::cout << "Не положительный размер системы" << std::endl;
		fclose(buo);
		fclose(bua);
		return 3;
	}

	// Выделяем память для СЛАУ, ответа жюри и ответа участника 
	Sole * S = new Sole(n);// Участника
	double * ans = new double[n];

	// Считываем СЛАУ
	for (int i = 0; i < n; i++)
		fread(S->A[i], sizeof(**S->A), n, buo);
	fread(S->b, sizeof(*S->b), n, buo);

	// Считываем ответ участника и жюри
	fread(S->x, sizeof (*S->x), n, buo);
	fread(ans, sizeof(*ans), n, bua);

	double res1 = 0, res2 = 0;
	for (int i = 0; i < n; i++) {
		res1 += S->A[0][i] * S->x[i];
		res2 += S->A[0][i] * ans[i];
	}
	std::cout << res1 << " - " << res2 << " = " << S->b[0] << std::endl;

	fclose(bua);
	fclose(buo);

	// Вычисляем ошибку, как квадрат нормы разности решений 
	double diff = 0.0; 
	for (int i = 0; i < n; i++) 
		diff += (ans[i] - S->x[i]) * (ans[i] - S->x[i]);

	// Проверяем, что ошибка мала, тогда сообщаем, что решение корректно, иначе - некорректно. 
	if (diff < 1e-6) { 
		std::cout << "Совпадает" << std::endl;
		checker_result.write_message ("AC. Numbers are equal."); 
		checker_result.write_verdict (verdict::AC); 
	} 
	else { 
		std::cout << "Не совпадает" << std::endl;
		checker_result.write_message ("WA. Output is not correct."); 
		checker_result.write_verdict (verdict::WA); 
	}

	delete[] ans;

	// Записываем время в правильной размерности (интервалы по 100 нс = 10 ^ (-7) сек). 
	checker_result.write_time (res_time * 1e7);

	return 0;
}
