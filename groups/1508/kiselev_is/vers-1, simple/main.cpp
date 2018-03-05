//  Вычисление многомерных интегралов с использованием многошаговой схемы (метод трапеций).

#include "Func.h"
#include "Math.h"
#include "Generate.h"

int main(int argc, char** argv) {
	// открытие файлов
	std::ifstream fin("test_for_program_in.txt");
	std::ofstream fout("test_for_program_out.txt");
	
	// считывание условий
	double result = 0.0;
	int size = 0;
	double res = 0.0;
	double interval[2];
	double accuracy = 0.1;
	for (int i = 0; i < 5; i++) {						// 5 тестов
		fin >> size;										// считываем размер функции

		Func fun(size);										// создаем функцию
		double* coef = new double(size);					// считываем коэфы
		for (int i = 0; i < size; i++) {
			fin >> coef[i];
		}			
		fun.SetCoeffs(coef);
		fin >> interval[0] >> interval[1];			// считываем промежуток
		fin >> accuracy;							// точность
		// запуск програамы и вывод результатов в файл
		res = Math::TIntegral(&fun, interval[0], interval[1], accuracy);
		fout << res << " Expected: " << Math::TIntegral(&fun, interval[0], interval[1], 0.000001 , 1000) << std::endl;
	}
	
	fin.close();
	fout.close();

	// Генератор
	Generate();
	// выполнение генерируемых тестов
	std::ifstream gin("generate.txt");
	std::ofstream gout("generate_out.txt");

	for (int i = 0; i < test_numb; i++) {						// 5 тестов
		gin >> size;										// считываем размер функции

		Func fun(size);										// создаем функцию
		double* coef = new double(size);					// считываем коэфы
		for (int i = 0; i < size; i++) {
			gin >> coef[i];
		}
		fun.SetCoeffs(coef);
		gin >> interval[0] >> interval[1];			// считываем промежуток
		gin >> accuracy;							// точность
													// запуск програамы и вывод результатов в файл
		res = Math::TIntegral(&fun, interval[0], interval[1], accuracy);
		gout << res << " Expected: " << Math::TIntegral(&fun, interval[0], interval[1], 0.0000001, 1000) << std::endl;
	}

	gin.close();
	gout.close();

	return 0;
}