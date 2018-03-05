//  Вычисление многомерных интегралов с использованием многошаговой схемы (метод трапеций).

#include "Func.h"
#include "Math.h"

int main(int argc, char** argv) {
	// данная программа выполняется для линейных функций
	Func fun(2);
	double coef[2] = { 0.5 , 2.0 };
	fun.SetCoeffs(coef);	
	std::cout << Math::TIntegral(&fun, 0.0, 4.0, 2 ) << std::endl;
	fun.PrintFunc();
	system("pause");
	return 0;
}