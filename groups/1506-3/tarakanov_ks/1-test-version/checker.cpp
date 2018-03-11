#include <cstdio> 
#include <cmath> 
#include <string>
#include <iostream>
#include <string>

using namespace std;

void StringName_to_CharName(string str, char* ch);
int Order(int num);
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
	void write_type(type t) 
	{ 
		//char ch = static_cast<int>(t) + '0';
		//fwrite(&ch, sizeof(char), 1, res);

		fwrite(&t, sizeof(t), 1, res);
	}

	// Сообщить тестирующей системе, что установлен один из вердиктов
	void write_verdict(verdict v) 
	{
		write_type(type::VERDICT);
		//char ch = static_cast<int>(v) + '0';
		//fwrite(&ch, sizeof(char), 1, res);

		fwrite(&v, sizeof (v), 1, res); 
	}
	
	// Написать сообщение пользователю о корректномти решения
	void write_message(string str)
	{ 
		write_type(type::MESSAGE); 
		int l = str.size ();
		//int order = Order(l);
		//char* ch = new char[order];
		//_itoa_s(l, ch, str.size(), 10);
		//fwrite(ch, sizeof (char), order, res);

		fwrite(&l, sizeof(l), 1, res);
		fwrite (&str[0], sizeof (str[0]), l, res); 
	}

	// Сообщить тестирующей системе время работы программы участника,  
	// x имеет размерность 100 нс = 10 ^ (-7) сек 
	void write_time(double x)
	{ 
		write_type(type::TIME);

		int order = Order(x);
		char* ch = new char[order];
		_itoa_s(x, ch, 100, 10);
		fwrite(ch, sizeof (char), order + 1, res);

		//fwrite(&x, sizeof (x), 1, res); 
	}

} checker_result; 


int main(int argc, char * argv[])
{ 
	// Имена файлов
	char* fileIN = "matr.in";
	char* fileOUT = "matr.out";
	char* answer = "answer.ans";

	if (argc > 1)
	{
		// Формируем новое имя файла с матрицами
		fileIN = argv[1];
		// Формируем новое имя выходного файла
		string str = string(argv[1]) + string(".out");
		fileOUT = new char[str.length()];
		StringName_to_CharName(str, fileOUT);
		str = string(argv[1]) + string(".ans");
		answer = new char[str.length()];
		StringName_to_CharName(str, answer);
	}


	// Открываем файл входных данных,  ответ участника 
	FILE * bui;
	fopen_s(&bui, fileIN, "rb");
	FILE * buo;
	fopen_s(&buo, fileOUT, "rb");
	// Открываем эталон
	FILE * perfect;
	fopen_s(&perfect, answer, "rb");
	



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
	for (int i = 0; i < N; i++)
	{
		fread(ans[i], sizeof(double), N, buo);
	}
	fread(&ans_time, sizeof(double), 1, buo);
  
	// Считываем время работы программы и матрицу жюри 
	for (int i = 0; i < N; i++)
	{
		fread(res[i], sizeof(double), N, perfect);
	}
	fread(&res_time, sizeof(double), 1, perfect);

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
		   
	// Записывем время, сек 
	checker_result.write_time (res_time);

	fclose(buo);
	fclose(bui);
	fclose(perfect);

	return 0;
}

void StringName_to_CharName(string str, char* ch)
{
	for (int i = 0; i < str.length(); i++)
		ch[i] = str[i];
}

int Order(int num)
{
	int order = 0;

	while (num) 
	{
		num /= 10;
		order++;
	}

	return order;
}