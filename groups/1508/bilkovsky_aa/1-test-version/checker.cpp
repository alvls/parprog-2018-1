#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <ccomplex>

using namespace std;

/* // Checker может устанавливать вот эти три вердикта:
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
DE = Deadly Error = Ошибка тестирующей системы */

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result {
private:
	FILE * bur;
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
	result(bool read = false)
	{
		if (read) bur = fopen("result.txt", "r");
		else
			bur = fopen("result.txt", "w");
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
		write_type(ext_cls::VERDICT);
		fwrite(&v, sizeof(v), 1, bur);
	}

	// Написать сообщение от checker'a пользователю.
	//   Например, что решение верное, или неверное.
	//   Использовать только латинские буквы и знаки препинания
	void write_message(string str)
	{
		write_type(ext_cls::MESSAGE);
		int l = str.size(); fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);
	}

	// Сообщить тестирующей системе время работы программы участника,
	//   вычисленное с помощью before_code
	// x имеет размерность 100 нс = 10 ^ (-7) сек
	void write_time(long long x)
	{
		write_type(ext_cls::TIME);
		fwrite(&x, sizeof(x), 1, bur);
	}

	// Сообщить тестирующей системе, память затребованную программой участника
	void write_memory(unsigned long long x)
	{
		write_type(ext_cls::MEMORY);
		fwrite(&x, sizeof(x), 1, bur);
	}
} checker_result;

int main(int argc, char* argv[]) {

	char* output = "../tests/0.out";	
	char* answer = "../tests/0.ans";	

	if (argc > 1)
	{
		output = argv[1];
		if (argc > 2)
			answer = argv[2];
	}
	

	// Открываем файл входных данных, файл выходных данных и ответ участника
	FILE * buo = fopen(output, "rb");
	FILE * bua = fopen(answer, "rb");

	double res_time;
	double ans_time;

	int sizeO,sizeA;
						// Считываем время выполнения
	fread(&res_time, sizeof(res_time), 1, buo);
	fread(&ans_time, sizeof(ans_time), 1, bua);

	//Считываем размерность матриц
	fread(&sizeO, sizeof(sizeO), 1, buo);
	fread(&sizeA, sizeof(sizeA), 1, bua);

	if (sizeO != sizeA)
	{
		checker_result.write_message("WA. Output is not correct.");
		checker_result.write_verdict(verdict::WA);

		fclose(bua);
		fclose(buo);

		return 0;
	}

	int notNull;

	fread(&notNull, sizeof(notNull), 1, buo);

	// Выделяем память для матрицы ответа жюри и ответа участника
	vector<complex<int>> elements(notNull);
	vector<int> secondIndex(notNull);
	vector<int> position(sizeO + 1);

	vector<vector<complex<int>>> MatrixO(sizeO);
	vector<vector<complex<int>>> MatrixA(sizeO);
	for (int i = 0; i < sizeO; ++i)
	{
		MatrixO[i].resize(sizeO);
		MatrixA[i].resize(sizeO);
	}

	// Считываем матрицу участника
	fread(elements.data(), sizeof(elements[0]), notNull, buo);
	fread(secondIndex.data(), sizeof(secondIndex[0]), notNull, buo);
	fread(position.data(), sizeof(position[0]), sizeO + 1, buo);

	// Считываем матрицу жюри
	for (int i = 0; i < sizeO; ++i)
		fread(MatrixA[i].data(), sizeof(MatrixA[i][0]), sizeO, bua);

	//Переводим матрицу участника в стандартный вид
	for (int i = 0; i < sizeO; ++i)
	{
		int pos = position[i];
		while (pos < position[i + 1])
		{
			MatrixO[i][secondIndex[pos]] = elements[pos];
			pos++;
		}
	}
	
	// Вычисляем ошибку, как процент не совпадающих ненулевых элементов
	double diff = 0;
	for (int i = 0; i < sizeO; i++)
		for (int j = 0; j < sizeO; ++j)
		{
			if (MatrixA[i][j] != MatrixO[i][j])
			{
				diff++;
			}
		}
	// Проверяем, что ошибка мала, тогда сообщаем, что решение корректно, иначе - некорректно.
	if (diff/notNull < 0.01)
	{
		checker_result.write_message("AC. Numbers are equal.");
		checker_result.write_verdict(verdict::AC);
	}
	else
	{
		checker_result.write_message("WA. Output is not correct.");
		checker_result.write_verdict(verdict::WA);
	}

	// Записываем время в правильной размерности (интервалы по 100 нс = 10 ^ (-7) сек).
	checker_result.write_time(res_time * 1e7);

	fclose(bua);
	fclose(buo);

	return 0;
}