#include <cstdio> 
#include <cmath> 
#include <string>
#include <iostream>

using namespace std;

/* 
// Checker устанавливает два вердикта 
AC = Accepted(результат корректен)
WA = Wrong Answer(результат некорректен)
*/

enum verdict { NO = 1, AC, WA};

class Result 
{
private: 
	FILE * res; 
public: 

	enum type { NO = 1, VERDICT, MESSAGE, TIME, MEMORY }; 

	// К-р по умолчанию
	Result(bool read = false)
	{ 
		if (read) 
			fopen_s(&res, "result.txt", "r"); 
		else 
			fopen_s(&res,"result.txt", "w"); 
	}
	// Д-р
	~Result() { fclose(res); }
	// Запись типа сообщения
	void write_type(type t) { fwrite(&t, sizeof(t), 1, res); }

	// Сообщить тестирующей системе, что установлен один из вердиктов
	void write_verdict(verdict v) 
	{
		write_type(type::VERDICT); 
		fwrite(&v, sizeof (v), 1, res); 
	}
	
	// Написать сообщение пользователю о корректномти решения
	void write_message(string str)
	{ 
		write_type(type::MESSAGE); 
		int l = str.size (); 
		fwrite(&l, sizeof (l), 1, res);
		fwrite (&str[0], sizeof (str[0]), l, res); 
	}

	// Сообщить тестирующей системе время работы программы участника,  
	// x имеет размерность 100 нс = 10 ^ (-7) сек 
	void write_time(long long x)
	{ write_type(type::TIME); fwrite(&x, sizeof (x), 1, res); }

} checker_result; 


int main() 
{ 
	// Открываем файл входных данных,  ответ участника 
	FILE * bui;
	fopen_s(&bui, "matr.in", "rb");
	FILE * buo;
	fopen_s(&buo, "matr.out", "rb");
	// Открываем эталон
	FILE * perfect;
	fopen_s(&perfect, "answer.out", "rb");
	
	int N; 
	// Считываем размерность матриц 
	fread(&N, sizeof (N), 1, bui);

	int block_size; 
	// Считываем размер блока
	fread(&block_size, sizeof(block_size), 1, bui);

	// Выделяем память для матрицы ответа жюри и ответа участника
	double **ans = new double*[N];
	for (int count = 0; count < N; count++)
		ans[count] = new double[N];

	double **res = new double*[N];
	for (int count = 0; count < N; count++)
		res[count] = new double[N];

	// Времена работы жюри и участника 
	double ans_time, res_time;
	
	// Считываем время работы программы участника и матрицу участника 
	fread(&ans_time, sizeof (int), 1, buo); 
	for (int i = 0; i < N; i++)
	{
		fread(ans[i], sizeof(double), N, buo);
	}
  
	// Считываем время работы программы и матрицу жюри 
	fread(&res_time, sizeof (int), 1, perfect); 
	for (int i = 0; i < N; i++)
	{
		fread(res[i], sizeof(double), N, perfect);
	}

	bool flag = true;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (res[i][j] != ans[i][j])
			{
				flag = false;
				break;
			}
		}
	}

		   
	// Если ошибки нет, сообщаем что решение корректно
	if (flag)
	{ 
		checker_result.write_message ("AC. Numbers are equal.");
		checker_result.write_verdict (verdict::AC); 
	} 
	else 
	{ 
		checker_result.write_message ("WA. Output is not correct."); 
		checker_result.write_verdict (verdict::WA); 
	}
		   
	// Записываем время в правильной размерности (интервалы по 100 нс = 10 ^ (-7) сек). 
	checker_result.write_time (res_time * 1e7);

	fclose(buo);
	fclose(bui);
	fclose(perfect);

	return 0;
}