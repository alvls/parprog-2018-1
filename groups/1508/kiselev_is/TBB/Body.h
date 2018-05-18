#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define parts 2000

#include "tbb4vc14.4.4.5/build/native/include/tbb/tbb.h"

#include <omp.h> 
#include <math.h>
#include <cmath>
#include "Func.h"

using namespace tbb;


// «начение функции в точке
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

// ћодуль
double module(double a) {
	return (a > 0) ? a : -a;
}




template <typename T>
class Body {
private:
	Func * _fun;
	double _XHigh;
	double _YHigh;

	double _Xpart;
	double _Ypart;
	double _Xpoint;
	double _Ypoint;

	double _Xstart;
	double _Xfinish
	double _Ystart;
	double _Yfinish;

	int thread;

public:
	blocked_range <int> range;
	double _res;

	Body(Func* fun, blocked_range<int> & rang, double Xstart, double Xfinish, double Ystart, double Yfinish) {
		_fun = fun;
		_res = 0.0;
		_XHigh = 0.0;
		_YHigh = 0.0;
		_Xpoint = 0.0;
		_Ypoint = 0.0;

		_Ystart = Ystart;
		_Yfinish = Yfinish;

		_Xstart = Xstart;
		_Xfinish = Xfinish;

		_Xpart = (_Xfinish - _Xstart) / parts;
		_Ypart = (_Yfinish)) - _Ystart) / parts;
		
		range = rang;

	};

	~Body() {};

	Body(Body& bod, split()) {
		range(bod.range, split());
	};

	void operator()(const blocked_range<int>& r){
		
		for (int i = range.begin(); i < range.end(); i++) {

			Xpoint = Xstart + (Xpart * i);
			XHigh = ((valueIn(fun, Xpoint, Ypoint) + valueIn(fun, Xpoint + Xpart, Ypoint)) / 2);

			variable = XHigh;
			// (F0 + F1) / 2  // определение среднего значени€ трапеции по х
			for (int j = 0; j < parts; j++) {

				YHigh = ((valueIn(fun, Xpoint, Ypoint + Ypart) + valueIn(fun, Xpoint, Ypoint + Ypart)) / 2);

				// (F0 + F1) / 2  // определение среднего значени€ трапеции через шаг по оси Y
				res = res + ((YHigh + variable) / 2 * Xpart * Ypart); // среднее между этими значени€ми
				variable = YHigh;
				Ypoint += Ypart;

			}
			Ypoint = Ystart;
		}

	}

	void join(Body & rhs) {
		res += rhs._res;
	};


	double Result() {
		return res;
	}

};
