#pragma once

#include <iostream>

class Func {
private:
	double* parameters[7];	// коэff , степень X, Y, степерь X в cos(x,y), sin(x,y) , степерь Y в cos(x,y) , sin(x,y);  массив 7*size
	int _size;				// размерность функции количество слагаемых
public:
	Func(int size) {
		_size = size;
		for (int i=0; i < 7; i++) {
			parameters[i] = new double(size);
		}
	}
	// конструктор
	~Func() {}
	// деструктор
	void SetCoeffs(double* coeff) {
		for (int i = 0; i < _size; i++)
			parameters[0][i] = coeff[i];
	}
	// установить коэффициенты
	double GetCoeff(int pos) {
		return parameters[0][pos];
	}
	// вернуть коэффициент №
	double GetXindex(int pos) {
		return parameters[1][pos];
	}

	double GetYindex(int pos) {
		return parameters[2][pos];
	}

	double GetXcos(int pos) {						// Показатель степени в cos(x,y)
		return parameters[3][pos];
	}

	double GetYcos(int pos) {						// Показатель степени в cos(x,y)
		return parameters[4][pos];
	}

	double GetXsin(int pos) {						// Показатель степени в sin(x,y)
		return parameters[5][pos];
	}

	double GetYsin(int pos) {						// Показатель степени в sin(x,y)
		return parameters[6][pos];
	}

	// вернуть коэффициент №
	void SetXindexs(double* coeff) {
		for (int pos=0; pos <_size; pos++)
		parameters[1][pos] = coeff[pos];
	}

	void SetYindexs(double* coeff) {
		for (int pos = 0; pos <_size; pos++)
			parameters[2][pos] = coeff[pos];
	}

	void SetXcos(double* coeff) {						// Показатель степени в cos(x,y)
		for (int pos = 0; pos <_size; pos++)
			parameters[3][pos] = coeff[pos];
	}

	void SetYcos(double* coeff) {						// Показатель степени в cos(x,y)
		for (int pos = 0; pos <_size; pos++)
			parameters[4][pos] = coeff[pos];
	}

	void SetXsin(double* coeff) {						// Показатель степени в sin(x,y)
		for (int pos = 0; pos <_size; pos++)
			parameters[5][pos] = coeff[pos];;
	}

	void SetYsin(double* coeff) {						// Показатель степени в sin(x,y)
		for (int pos = 0; pos <_size; pos++)
			parameters[6][pos] = coeff[pos];
	}

	int GetSize() {
		return _size;
	}
	// вернуть размерность полинома

	// 1 вариант : зная, что на каком месте стоит брать индекс [s][f]
	// 2 вариант : Для улучшения понимания сделать 6 fункций GetYcos();

	void PrintFunc() {
		for (int i = 0; i < _size; i++) {
			std::cout << GetCoeff(0) << " * x ^ " << GetXindex(0) << " * y ^ " << GetYindex(0);
			if ((GetXcos(0) != 0) || (GetYcos(0) != 0))
				std::cout << " * cos ( x^" << GetXcos(0) << " * y^" << GetYcos(0) << " )";
			if ((GetXsin(0) != 0) || (GetYsin(i) != 0))
				std::cout << " * sin ( x^" << GetXsin(0) << " * y^" << GetYsin(0) << " )";
		}
		std::cout << std::endl;
	}
	// Вывод массива
};