// Программа проверки правильности решения
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>

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
		if (read) bur = fopen((".\\tests\\" + string("result.txt")).c_str(), "r"); 
		else bur = fopen((".\\tests\\" + string("result.txt")).c_str(), "a");
	}
	~result() 
	{ 
		fprintf(bur, "\n");
		fclose(bur); 
	}
	void write_type(ext_cls t)
	{
		/*fwrite(&t, sizeof(t), 1, bur);*/
		switch (t)
		{
		case NO:
			fprintf(bur, "%s", "NO");
			break;
		case VERDICT:
			fprintf(bur, "%s", "VERDICT");
			break;
		case MESSAGE:
			fprintf(bur, "%s", "MESSAGE");
			break;
		case TIME:
			fprintf(bur, "%s", "TIME");
			break;
		case MEMORY:
			fprintf(bur, "%s", "MEMORY");
			break;
		}
	}
	// Сообщить тестирующей системе, что решение получило один из вердиктов verdict
	void write_verdict(verdict v)
	{
		write_type(ext_cls::VERDICT);
		/*fwrite(&v, sizeof(v), 1, bur);*/
		fprintf(bur, " ");
		switch (v)
		{
		case AC:
			fprintf(bur, "%s", "AC");
			break;
		case WA:
			fprintf(bur, "%s", "WA");
			break;
		case PE:
			fprintf(bur, "%s", "PE");
			break;
		}
	}
	// Написать сообщение от checker'a пользователю.
	// Например, что решение верное, или неверное.
	// Использовать только латинские буквы и знаки препинания
	void write_message(string str)
	{
		write_type(ext_cls::MESSAGE);
		int l = str.size();
		/*fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);*/
		//fprintf(bur, "%i", l);
		fprintf(bur, "%s", (" " + str).c_str());
	}
	// Сообщить тестирующей системе время работы программы участника,
	// вычисленное с помощью before_code
	// x имеет размерность 100 нс = 10 ^ (-7) сек
	void write_time(double x)
	{
		fprintf(bur, " ");
		write_type(ext_cls::TIME);
		/*fwrite(&x, sizeof(x), 1, bur);*/
		fprintf(bur, " %f sec", x);
	}
	// Сообщить тестирующей системе, память затребованную программой участника
	void write_memory(unsigned long long x)
	{
		write_type(ext_cls::MEMORY);
		/*fwrite(&x, sizeof(x), 1, bur);*/
		fprintf(bur, "%llu", x);
	}
};
////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[])
{
	result checker_result;

	FILE * res_file = fopen((".\\tests\\" + std::string(argv[1]) + ".ans").c_str(), "rb");
	FILE * ans_file = fopen((".\\tests\\" + std::string(argv[1]) + "_true.ans").c_str(), "rb");

	// Время работы программы участника и жюри
	double ans_time, res_time;
	// Считываем время работы программы участника и жюри
	fread(&res_time, sizeof(res_time), 1, res_file);
	fread(&ans_time, sizeof(res_time), 1, ans_file);
	// Размерность массива
	int n;
	// Считываем размерность массива
	fread(&n, sizeof(n), 1, res_file);
	fseek(ans_file, sizeof(n), SEEK_CUR);
	// Выделяем память для массива ответа жюри и ответа участника
	vector<int> res(n), ans(n);
	// Считываем массив участника
	fread(res.data(), sizeof(int), n, res_file);
	// Считываем массив жюри
	fread(ans.data(), sizeof(int), n, ans_file);
	// Флаг равенства решений
	bool isEqual = true;
	// Ищем несовпадение
	for (size_t i = 0; i < n && isEqual; ++i)
		if (res[i] != ans[i])
			isEqual = false;
	// Проверяем, что ошибки нет, тогда сообщаем, что решение корректно, иначе - некорректно.
	if (isEqual)
	{
		checker_result.write_message("test #" + string(argv[1]) + ": AC. Numbers are equal. ");
		checker_result.write_verdict(verdict::AC);
	}
	else
	{
		checker_result.write_message("test #" + string(argv[1]) + ": WA. Output is not correct. ");
		checker_result.write_verdict(verdict::WA);
	}
	// Записываем время
	checker_result.write_time(res_time);

	fclose(res_file);
	fclose(ans_file);
	return 0;
}
