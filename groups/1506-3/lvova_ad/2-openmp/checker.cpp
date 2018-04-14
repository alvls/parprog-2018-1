#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm> 
#include <iostream>
using namespace std;

// Используется для взаимодействия с тестирующей системой
////////////////////////////////////////////////////////////////////////////////////////////
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
class result
{
private:
	FILE * bur;
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };

	result(bool read = false)
	{
		if (read) bur = fopen("result.txt", "r"); else bur = fopen("result.txt", "w");
	}

	~result() 
	{ 
		fclose(bur);
	}

	void write_type(ext_cls t)
	{
		fwrite(&t, sizeof(t), 1, bur);
	}

	// Сообщить тестирующей системе, что решение получило один из вердиктов verdict
	void write_verdict(verdict v)
	{
		write_type(ext_cls::VERDICT); fwrite(&v, sizeof(v), 1, bur);
	}

	// Написать сообщение от checker' a пользователю.
	//  Например, что решение верное, или неверное.
	// Использовать только латинские буквы и знаки препинания
	void write_message(string str)
	{
		write_type(ext_cls::MESSAGE); int l = str.size(); fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);
	}

	// Сообщить тестирующей системе время работы программы участника,
	// вычисленное с помощью before_code
	// x имеет размерность 100 нс = 10 ^ ( -7) сек

	void write_time(long long x)
	{
		write_type(ext_cls::TIME); fwrite(&x, sizeof(x), 1, bur);
	}

	// Сообщить тестирующей системе, память затребованную программой участника
	void write_memory(unsigned long long x)
	{
		write_type(ext_cls::MEMORY); fwrite(&x, sizeof(x), 1, bur);
	}
} checker_result;
////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	// Открываем файл входных данных, файл выходных данных и ответ участника
	FILE * bui = fopen("../massiv.in", "rb");
	FILE * buo = fopen("../massiv.out", "rb");
	int size;
	double res_time;


	// Считываем время работы программы участника
	fread(&res_time, sizeof(res_time), 1, buo);

	// Считываем размерность массива
	fread(&size, sizeof(size), 1, bui);
	fread(&size, sizeof(size), 1, buo);


	// Выделяем память для массива ответа жюри и ответа участника
	double * answer = new double[size], * result = new double[size];
	
	// Считываем  массив участника
	fread(result, sizeof(*result), size, buo);

	// Считываем исходные данные для проверки стандартной функцией
	fread(answer, sizeof(*answer), size, bui);

	//сортируем исходные данные сортировкой std
	sort(answer, answer+size);

	//Сравниваем ответы
	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		if (answer[i] != result[i])
		{
            double k = result[i];
            std::cout << std::endl << "Numbers isn't equal - " << i << ";" << answer[i] << ";" << k << std::endl;
			checker_result.write_message("WA. Output is not correct.");
			checker_result.write_verdict(verdict::WA);
			flag = true;
			break;
		}
	}
	if(!flag)
	{
		std::cout << std::endl << "Numbers are equal" << std::endl;
		checker_result.write_message("AC. Numbers are equal.");
		checker_result.write_verdict(verdict::AC);
	}
	
	// Записываем время в правильной размерности ( интервалы по 100 нс = 10 ^ (-7) сек).
	checker_result.write_time(res_time * 1e7);
	fclose(bui);
	fclose(buo);
	return 0;
}