//  Вычисление многомерных интегралов с использованием многошаговой схемы (метод трапеций).

#include "Func.h"
#include "Math.h"

int main(int argc, char** argv) {
	// данная программа выполняется для линейных функций
	Func fun(3);
	double coef[3] = { -1.0 , 2.0, 0.0 };
	fun.SetCoeffs(coef);	
	std::cout << Math::TIntegral(&fun, 0.0, 2.0, 0.001 ) << std::endl;
	fun.PrintFunc();
	system("pause");
	return 0;
}