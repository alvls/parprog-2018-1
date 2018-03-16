#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cmath>
#include <string>
#include <vector>

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
		fwrite(&v, sizeof (v), 1, bur);
	} 

		   // Написать сообщение от checker'a пользователю.
		   //   Например, что решение верное, или неверное.
		   //   Использовать только латинские буквы и знаки препинания
	void write_message(string str)
	{ 
		write_type(ext_cls::MESSAGE);
		int l = str.size (); fwrite(&l, sizeof (l), 1, bur);
		fwrite (&str[0], sizeof (str[0]), l, bur);
	} 

		   // Сообщить тестирующей системе время работы программы участника,
		   //   вычисленное с помощью before_code
		   // x имеет размерность 100 нс = 10 ^ (-7) сек
	void write_time(long long x)
	{ 
		write_type(ext_cls::TIME);
		fwrite(&x, sizeof (x), 1, bur);
	} 

		   // Сообщить тестирующей системе, память затребованную программой участника
	void write_memory(unsigned long long x)    
	{ 
		write_type(ext_cls::MEMORY);
		fwrite(&x, sizeof (x), 1, bur);
	} 
} checker_result; 

int main(int argc, char* argv[]) {

//	char* PATHin = "matr.in";	//default input file name
	char* PATHout = "matr.out";	//default output file name
	char* PATHans = "matr.ans";	//default answer file name


	if (argc > 1)
	{
		PATHout = argv[1];
		if (argc > 2)
			PATHans = argv[2];
	}

	// Открываем файл входных данных, файл выходных данных и ответ участника
//	FILE * bui = fopen(PATHin, "rb"); //is it necessary?
	FILE * buo = fopen(PATHout, "rb");
	FILE * bua = fopen(PATHans, "rb");

	double timeO;
	double timeA;

	int matrixSizeO;	//output matrix size
	int matrixSizeA;	//answer matrix size

	// Считываем время выполнения
	fread(&timeO, sizeof(timeO), 1, buo);
	fread(&timeA, sizeof(timeA), 1, bua);

	//Считываем размер матриц
	fread(&matrixSizeO, sizeof(matrixSizeO), 1, buo);
	fread(&matrixSizeA, sizeof(matrixSizeA), 1, bua);

	if (matrixSizeO != matrixSizeA)
	{
		checker_result.write_message("WA. Output is not correct.");
		checker_result.write_verdict(verdict::WA);

//		fclose(bui);
		fclose(bua);
		fclose(buo);

		return 0;
	}

	int notZero;

	fread(&notZero, sizeof(notZero), 1, buo);

	 // Выделяем память для матрицы ответа жюри и ответа участника
	vector<double> value(notZero);
	vector<int> col(notZero);
	vector<int> row(matrixSizeO + 1);

	vector<vector<double>> standartMatrO(matrixSizeO);
	vector<vector<double>> standartMatrA(matrixSizeA);
	for (int i = 0; i < matrixSizeA; ++i)
	{
		standartMatrO[i].resize(matrixSizeO);
		standartMatrA[i].resize(matrixSizeA);
	}

	// Считываем матрицу участника
	fread(value.data(), sizeof(value[0]), notZero, buo);
	fread(col.data(), sizeof(col[0]), notZero, buo);
	fread(row.data(), sizeof(row[0]), matrixSizeO + 1, buo);

	 // Считываем матрицу жюри
	for (int i = 0; i < matrixSizeA; ++i)
		fread(standartMatrA[i].data(), sizeof(standartMatrA[i][0]), matrixSizeA, bua);

	//Переводим матрицу участника в стандартный вид
	for (int i = 0; i < matrixSizeO; ++i)
	{
		int pos = row[i];
		while (pos < row[i + 1])
		{
			standartMatrO[i][col[pos]] = value[pos];
			pos++;
		}
	}

	// Вычисляем ошибку, как квадрат нормы разности решений
	double diff = 0.0;
	for (int i = 0; i < matrixSizeO; i++)
		for (int j = 0; j < matrixSizeO; ++j)
			diff += (standartMatrA[i][j] - standartMatrO[i][j]) * (standartMatrA[i][j] - standartMatrO[i][j]);

	 // Проверяем, что ошибка мала, тогда сообщаем, что решение корректно, иначе - некорректно.
	if (diff < 1e-6)
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
	checker_result.write_time (timeO);

	fclose(bua);
	fclose(buo);

	return 0;
}
