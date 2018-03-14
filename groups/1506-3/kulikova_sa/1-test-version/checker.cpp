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


//argv[1] - имя выходного файла, argv[2] - имя файла ответа
int main(int argc, char * argv[]) {
	// Открываем файл выходных данных и ответ участника  
	FILE * buo = fopen(argv[1], "rb"); 
	FILE * bua = fopen(argv[2], "rb");

	// Время работы участника и время работы жюри
	double ans_time, res_time;

	// Считываем время работы программы участника и жюри
	fread(&res_time, sizeof(res_time), 1, buo);
	fread(&ans_time, sizeof(ans_time), 1, bua);

	int n; 
	// Считываем размерность матриц 
	fread(&n, sizeof (n), 1, buo);

	// Выделяем память для СЛАУ, ответа жюри и ответа участника 
	Sole * S = new Sole(n);// Участника
	double * ans = new double[n], * res = new double[n]; 

	// Считываем СЛАУ
	for (int i = 0; i < n; i++)
		fread(S->A[i], sizeof(**S->A), n, buo);
	fread(S->b, sizeof(*S->b), n, buo);

	// Считываем ответ участника 
	fread(res, sizeof (*res), n, buo);

	// Считываем ответ жюри 
	fread(ans, sizeof (*ans), n, bua);

	// Вычисляем ошибку, как квадрат нормы разности решений 
	double diff = 0.0; 
	for (int i = 0; i < n; i++) 
		diff += (ans[i] - res[i]) * (ans[i] - res[i]);

	// Проверяем, что ошибка мала, тогда сообщаем, что решение корректно, иначе - некорректно. 
	if (diff < 1e-6) { 
		checker_result.write_message ("AC. Numbers are equal."); 
		checker_result.write_verdict (verdict::AC); 
	} 
	else { 
		checker_result.write_message ("WA. Output is not correct."); 
		checker_result.write_verdict (verdict::WA); 
	}

	// Записываем время в правильной размерности (интервалы по 100 нс = 10 ^ (-7) сек). 
	checker_result.write_time (res_time * 1e7);

	fclose(bua); 
	fclose(buo);

	return 0;
}
