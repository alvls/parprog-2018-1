
#pragma once

#include <math.h>
#include <cmath>
#include "Func.h"

// Значение функции в точке
double valueIn(Func* fun, double Xpoint, double Ypoint) {
	double result = 0.0;
	double point = 0.0;
	int size = fun->GetSize();
	for (int i = 0; i < size; i++) {
		point = fun->GetCoeff(i)*(pow(Xpoint, fun->GetXindex(i))) * pow(Ypoint, fun->GetYindex(i));
		if ((fun->GetXcos(i) != 0) || (fun->GetYcos(i) != 0))
			point = point * cos(pow(Xpoint, fun->GetXcos(i))*pow(Ypoint, fun->GetYcos(i)));
		if ((fun->GetXsin(i) != 0) || (fun->GetYsin(i) != 0))
			point = point * sin(pow(Xpoint, fun->GetXsin(i))*pow(Ypoint, fun->GetYsin(i)));
		result = result + point;
	}
	return result;
};

// Модуль
double module(double a) {
	return (a > 0) ? a : -a;
}

// Интеграл трапециями, функция, начало отрезка, конец, точность, начальное количество частей

double TIntegral(Func* fun, double start, double finish, double accuracy, int parts = 200) {

	double result = 0.0;

	double XHigh = 0.0;
	double YHigh = 0.0;

	double Xpart = (finish - start) / parts;
	double Ypart = Xpart;
	double Xpoint = start;
	double Ypoint = start;

	double variable = 0.0;
	double LastResult = valueIn(fun, (finish - start) / 2, (finish - start) / 2);
	while (module(result - LastResult) > accuracy) {

		for (int i = 0; i < parts; i++) {
			XHigh = ((valueIn(fun, Xpoint, Ypoint) + valueIn(fun, Xpoint + Xpart, Ypoint)) / 2);

			variable = XHigh;
			// (F0 + F1) / 2  // определение среднего значения трапеции
			for (int j = 0; j < parts; j++) {
				YHigh = ((valueIn(fun, Xpoint, Ypoint + Ypart) + valueIn(fun, Xpoint, Ypoint + Ypart)) / 2);

				// (F0 + F1) / 2  // определение среднего значения трапеции через шаг по оси Y
				result = result + ((YHigh + variable) / 2 * Xpart * Ypart); // среднее между этими значениями
				variable = YHigh;
				Ypoint = Ypoint + Ypart;

			}
			Ypoint = start;
			Xpoint = Xpoint + Xpart;
		}
		if (module(LastResult - result) > (accuracy / 20)) {
			if (module(LastResult - result) > accuracy * 100) parts += 1000;
			else if (module(LastResult - result) > accuracy * 10) parts += 200;
			else if (module(LastResult - result) > accuracy / 10) parts += 50;
			LastResult = result;
			result = 0;
			Xpart = (finish - start) / parts;
			Ypart = Xpart;
			Xpoint = start;
			Ypoint = start;

			std::cout << parts << std::endl;
		}

	}
	return result;
}

