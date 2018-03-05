#pragma once

#include "Func.h"

static class Math {
public:
	// Значение функции в точке
	static double valueIn(Func* fun, double point) {
		double result = 0;
		int size = fun->GetSize();
		for (int i = 0; i < size; i++) {
			result = result + fun->GetCoeff(i)*exponent(point, fun->GetIndex(i));
		}
		return result;
	}
	
	static double module(double a) {
		return (a > 0) ? a : -a;
	}

	// Значение числа в степени
	static double exponent(double value, int exp) {
		double result = 1.0;
		while (exp > 0) {
			result = result * value;
			exp--;
		}
		return result;
	}	

	// Интеграл трапециями
	static double TIntegral(Func* fun, double start, double finish, double accuracy) {
		int parts = 10;					// количество шагов
		double last_result = 0.0;		// последний вычисленный результат
		double result = 0.0;			// текущий результат
		double partValue = 0.0;			// размер шага
		double point = 0.0;
		do {
			point = start;
			if ((last_result != 0) && (module(result - last_result) >= accuracy * 5)) parts += 9;
			last_result = result;
			result = 0.0;
			parts++;
			partValue = (finish - start) / parts;
			for (int i = 0; i < parts; i++) {
				result = result + ((valueIn(fun, point) + valueIn(fun, point + partValue)) / 2 * partValue);
				// (F0 + F1) / 2 * H  // значение высоты в средней точке трапеции * ширину основания
				point = point + partValue;
			}
		} 
		while (module(result - last_result) > accuracy);		// пока погрешность в вычислениях больше
		return result;
	}
};
