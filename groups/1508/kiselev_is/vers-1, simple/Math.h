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
	static double TIntegral(Func* fun, double start, double finish, int parts = 1) {
		double partValue = (finish - start) / parts;	// размер шага
		double result = 0.0;
		double point = start;
		while (parts > 0) {
			result = result + ( ( valueIn(fun, point) + valueIn(fun, point + partValue) ) / 2 * partValue );
				// (F0 + F1) / 2 * h
			point = point + partValue;	
			parts--;
		}
		return result;
	}
};
