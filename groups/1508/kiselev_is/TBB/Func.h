#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

class Func {
private:
	double* parameters[7];	// ���ff , ������� X, Y, ������� X � cos(x,y), sin(x,y) , ������� Y � cos(x,y) , sin(x,y);  ������ 7*size
	int _size;				// ����������� ������� ���������� ���������
public:
	Func(int size) {
		_size = size;
		for (int i = 0; i < 7; i++) {
			parameters[i] = new double(size);
		}
	}
	// �����������
	~Func() {}
	// ����������
	void SetCoeffs(double* coeff) {
		for (int i = 0; i < _size; i++)
			parameters[0][i] = coeff[i];
	}
	// ���������� ������������
	double GetCoeff(int pos) {
		return parameters[0][pos];
	}
	// ������� ����������� �
	double GetXindex(int pos) {
		return parameters[1][pos];
	}

	double GetYindex(int pos) {
		return parameters[2][pos];
	}

	double GetXcos(int pos) {						// ���������� ������� � cos(x,y)
		return parameters[3][pos];
	}

	double GetYcos(int pos) {						// ���������� ������� � cos(x,y)
		return parameters[4][pos];
	}

	double GetXsin(int pos) {						// ���������� ������� � sin(x,y)
		return parameters[5][pos];
	}

	double GetYsin(int pos) {						// ���������� ������� � sin(x,y)
		return parameters[6][pos];
	}

	// ������� ����������� �
	void SetXindexs(double* coeff) {
		for (int pos = 0; pos <_size; pos++)
			parameters[1][pos] = coeff[pos];
	}

	void SetYindexs(double* coeff) {
		for (int pos = 0; pos <_size; pos++)
			parameters[2][pos] = coeff[pos];
	}

	void SetXcos(double* coeff) {						// ���������� ������� � cos(x,y)
		for (int pos = 0; pos <_size; pos++)
			parameters[3][pos] = coeff[pos];
	}

	void SetYcos(double* coeff) {						// ���������� ������� � cos(x,y)
		for (int pos = 0; pos <_size; pos++)
			parameters[4][pos] = coeff[pos];
	}

	void SetXsin(double* coeff) {						// ���������� ������� � sin(x,y)
		for (int pos = 0; pos <_size; pos++)
			parameters[5][pos] = coeff[pos];;
	}

	void SetYsin(double* coeff) {						// ���������� ������� � sin(x,y)
		for (int pos = 0; pos <_size; pos++)
			parameters[6][pos] = coeff[pos];
	}

	int GetSize() {
		return _size;
	}
	// ������� ����������� ��������

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
	// ����� �������
};