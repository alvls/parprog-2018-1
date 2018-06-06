#include "Dot.h"
#include <stdio.h>
#include <string>

#include <iostream>

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result
{
private:
	FILE * file;
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };

	result(bool read = false)
	{
		if (read) 
			file = fopen("../Checker_Result/result.txt", "r");
		else 
			file = fopen("../Checker_Result/result.txt", "w");
	}

	~result() 
	{ 
		fclose(file);
	}

	void write_type(ext_cls t) 
	{ 
		fwrite(&t, sizeof(t), 1, file);
	}
	
	void write_verdict(verdict v)
	{
		write_type(ext_cls::VERDICT);
		fwrite(&v, sizeof(v), 1, file);
	}

	void write_message(std::string str)
	{
		write_type(ext_cls::MESSAGE);
		int l = str.size();
		fwrite(&l, sizeof(l), 1, file);
		fwrite(&str[0], sizeof(str[0]), l, file);
	}

	void write_time(long long x)
	{
		write_type(ext_cls::TIME);
		fwrite(&x, sizeof(x), 1, file);
	}

	void write_memory(unsigned long long x)
	{
		write_type(ext_cls::MEMORY); fwrite(&x, sizeof(x), 1, file);
	}

} checker_result;

//Запуск через командную строку с вводом  1)имя файла выходных данных 2)файл с проверяемыми результатами
int main(int argc, char * argv[])
{
	//FILE * in_data = fopen(argv[1], "rb"); имя файлы входных данных(он не нужен)
	FILE * out_data = fopen(argv[1], "rb");
	FILE * checking_results = fopen(argv[2], "rb");
	int size;
	fread(&size, sizeof(size), 1, out_data);
	int checkingSize;
	fread(&checkingSize, sizeof(checkingSize), 1, checking_results);

	//Если кол-во точек в оболочках различно => Ответ неверный
	if (size != checkingSize)
	{
		checker_result.write_message("WA. Size not correct.");
		checker_result.write_verdict(verdict::WA);
		fclose(checking_results);
		fclose(out_data);
		return 0;
	}
	dot* dotArrayCorrect = new dot[size];
	dot* dotArrayCheck = new dot[size];
	fread(dotArrayCorrect, sizeof(*dotArrayCorrect), size, out_data);
	fread(dotArrayCheck, sizeof(*dotArrayCheck), size, checking_results);

	//Проверка корректности
	verdict verd = AC;
	for (auto i = 0; i < size; i++)
	{
		if (dotArrayCorrect[i] != dotArrayCheck[i])
			verd = WA;
	}
	if (verd == AC)
	{
		checker_result.write_message("AC. Answer is correct.");
		checker_result.write_verdict(verd);
	}
	else
	{
		checker_result.write_message("WA. Answer is not correct.");
		checker_result.write_verdict(verd);
	}

	fclose(checking_results);
	fclose(out_data);
	return 0;
}

