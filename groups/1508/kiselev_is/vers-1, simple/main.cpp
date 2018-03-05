//  Вычисление многомерных интегралов с использованием многошаговой схемы (метод трапеций).

#include "Func.h"
#include "Math.h"
#include <fstream>

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
		fin >> result;
		// запуск програамы и вывод результатов в файл
		res = Math::TIntegral(&fun, interval[0], interval[1], accuracy);
		fout << res << " Expected: " << result << std::endl;
	}
	
	fin.close();
	fout.close();
	return 0;
}