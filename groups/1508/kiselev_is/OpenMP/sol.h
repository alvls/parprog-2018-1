#pragma once

#include <omp.h> 
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

double TIntegral(Func* fun, double Xstart, double Xfinish, double Ystart, double Yfinish, double accuracy, int threads = 1 , int parts = 2000) {

	double result = 0.0;

	double XHigh = 0.0;
	double YHigh = 0.0;

	double Xpart = (Xfinish - Xstart) / parts;
	double Ypart = (Yfinish - Ystart) / parts;
	double Xpoint = Xstart;
	double Ypoint = Ystart;

	double variable = 0.0;
	
	#pragma omp parallel lastprivate(result) num_threads(threads) {
	#pragma omp for private(XHigh,YHigh,Xpoint,Ypoint,variable)

		for (int i = 0; i < parts; i++) {
			XHigh = ((valueIn(fun, Xpoint, Ypoint) + valueIn(fun, Xpoint + Xpart, Ypoint)) / 2);

			variable = XHigh;
			// (F0 + F1) / 2  // определение среднего значения трапеции по х
			for (int j = 0; j < parts; j++) {
				YHigh = ((valueIn(fun, Xpoint, Ypoint + Ypart) + valueIn(fun, Xpoint, Ypoint + Ypart)) / 2);

				// (F0 + F1) / 2  // определение среднего значения трапеции через шаг по оси Y
				result = result + ((YHigh + variable) / 2 * Xpart * Ypart); // среднее между этими значениями
				variable = YHigh;
				Ypoint = Ypoint + Ypart;

			}
			Ypoint = Ystart;
			Xpoint = Xpoint + Xpart;
		}
	}
	
	return result;
}

