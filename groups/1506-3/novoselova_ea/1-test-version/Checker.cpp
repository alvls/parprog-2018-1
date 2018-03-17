#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <string>
#include <fstream>
#include<iostream>
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
/*enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };
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
	~result() { fclose(bur); }
	void write_type(ext_cls t) { fwrite(&t, sizeof(t), 1, bur); }
	// Сообщить тестирующей системе, что решение получило один из вердиктов verdict
	void write_verdict(verdict v)
	{
		write_type(ext_cls::VERDICT); fwrite(&v, sizeof(v), 1, bur);
	}
	// Написать сообщение от checker'a пользователю.
	// Например, что решение верное, или неверное.
	// Использовать только латинские буквы и знаки препинания
	void write_message(string str)
	{
		write_type(ext_cls::MESSAGE); int l = str.size(); fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);
	}
	// Сообщить тестирующей системе время работы программы участника,
	// вычисленное с помощью before_code
	// x имеет размерность 100 нс = 10 ^ (-7) сек
	void write_time(long long x)
	{
		write_type(ext_cls::TIME); fwrite(&x, sizeof(x), 1, bur);
	}
	// Сообщить тестирующей системе, память затребованную программой участника
	void write_memory(unsigned long long x)
	{
		write_type(ext_cls::MEMORY); fwrite(&x, sizeof(x), 1, bur);
	}
} checker_result;*/

int MUL(int *MatrixA, int *MatrixB, int *MatrixC, int N);
int main(int argc, char *argv[])
{
	// Открываем файл входных данных, файл выходных данных и ответ участника
	char *filein = "1";
	char *fileout = "1.ans";
	if (argc > 1)
	{
		filein = argv[1];
		fileout = argv[2];
	}

	int n;
	double time;
	int *a, *b, *ans, *res;
	freopen(filein, "rb", stdin);
	fread(&n, sizeof(n), 1, stdin);
	a = new int[n * n];
	b = new int[n * n];
	fread(a, sizeof(*a), n * n, stdin);
	fread(b, sizeof(*b), n * n, stdin);
	fclose(stdin);
	res = new int[n * n];
	ans = new int[n * n];
	freopen(fileout, "rb", stdin);
	fread(&time, sizeof(time), 1, stdin);
	fread(res, sizeof(*res), n * n, stdin);
	fclose(stdin);
	MUL(a, b, ans, n);
	double diff = 0.0;
	for (int i = 0; i < n * n; i++)
		diff += (ans[i] - res[i]) * (ans[i] - res[i]);
	
	std::ofstream resultFile("result.txt");
	if (diff < 1e-6)
	{
		if (resultFile.is_open())
		{

			resultFile << "AC. Numbers are equal";
		}
		
	}
	else
	{
		if (resultFile.is_open())
		{

			resultFile << "WA. Output is not correct";
		}
	}
	return 0;
}