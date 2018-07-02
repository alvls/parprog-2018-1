#pragma once
#include <stddef.h>
#include <iostream>
#include <complex>
#include <omp.h>

using namespace std;

template <typename T>
class sparse_matrix
{
private:
	T * values;
	int values_size;
	int* koeff;
	int row_count;
	int column_count;
	int* lenghts;

public:
	T Zero();
	bool IsZero(T tmp);
	void Multyply_Matrix_on_Row(int num, sparse_matrix* B, int& row_size,
		T** value_mas, int** koeff_mas);
	void Multyply_Row_on_Element(T elem, int B_size, T* B_value, int* B_koeff,
		T* res);
	sparse_matrix* Matrix_Multyply(sparse_matrix* B);
	sparse_matrix<T>(int _row_count, int _column_count);
	sparse_matrix<T>();
	void SetValue(int _values_size, T* _values, int* _koeff, int* _lenghts);
	int Get_Row_Count();
	int Get_Column_Count();
	int Get_Size_Row(int k);
	void crs_to_standart(complex<double> ** s_values);
	void Get_Row(int num, int& size_row, T** val_point, int** koeff_point);
	void Show();
	~sparse_matrix();
};

template <typename T>
inline sparse_matrix<T>::sparse_matrix(int _row_count, int _column_count)
{
	row_count = _row_count;
	column_count = _column_count;
	lenghts = new int[row_count + 1];
}

template <typename T>
inline sparse_matrix<T>::sparse_matrix()
{
	row_count = 0;
	column_count = 0;
	//lenghts = new int[row_count + 1];
}


template <>
inline bool
sparse_matrix<std::complex<double>>::IsZero(std::complex<double> tmp)
{
	if ((tmp.real() == 0) && (tmp.imag() == 0))
		return true;
	else
		return false;
}
template <>
inline std::complex<double>
sparse_matrix<std::complex<double>>::Zero()
{
	return (0, 0);
}

template <typename T>
inline T
sparse_matrix<T>::Zero()
{
	return 0;
}

template <typename T>
inline bool
sparse_matrix<T>::IsZero(T tmp)
{
	if (tmp == 0)
		return true;
	else
		return false;
}

template <typename T>
inline void
sparse_matrix<T>::Multyply_Matrix_on_Row(int num, sparse_matrix* B,
	int& row_size, T** value_mas,
	int** koeff_mas)
{
	int result_row_size = B->Get_Column_Count();
	T* result_row = new T[result_row_size];
	for (int i = 0; i < result_row_size; i++) {
		result_row[i] = Zero();
	}
	int A_size;
	T* A_value = NULL;
	int* A_koeff = NULL;
	int B_size;
	T* B_value = NULL;
	int* B_koeff = NULL;
	int row_num;
	T A_element;
	this->Get_Row(num, A_size, &A_value, &A_koeff);
	if (A_size != 0) {
		for (int i = 1; i <= A_size; i++) {
			row_num = A_koeff[i - 1];
			A_element = A_value[i - 1];
			B->Get_Row(row_num + 1, B_size, &B_value, &B_koeff);
			Multyply_Row_on_Element(A_element, B_size, B_value, B_koeff, result_row);
		}
	}
	row_size = 0;
	for (int i = 0; i < result_row_size; i++) {
		if (IsZero(result_row[i]) == false)
			row_size++;
	}
	*value_mas = new T[row_size];
	*koeff_mas = new int[row_size];
	int counter = 0;
	for (int i = 0; i < result_row_size; i++) {
		if (IsZero(result_row[i]) == false) {
			(*value_mas)[counter] = result_row[i];
			(*koeff_mas)[counter] = i;
			counter++;
		}
	}
	delete (result_row);
}

template <typename T>
inline void
sparse_matrix<T>::Multyply_Row_on_Element(T elem, int B_size, T* B_value,
	int* B_koeff, T* res)
{
	T res_elem;
	for (int i = 0; i < B_size; i++) {
		res_elem = elem * B_value[i];
		res[B_koeff[i]] += res_elem;
	}
}

template <typename T>
inline sparse_matrix<T>*
sparse_matrix<T>::Matrix_Multyply(sparse_matrix* B)
{
	sparse_matrix<T>* C = new sparse_matrix<T>(row_count, B->Get_Column_Count());
	T** point_mas = new T*[row_count];
	int** koef_mas_point = new int*[row_count];
	int* sizes = new int[row_count];
#pragma omp parallel
	{
#pragma omp for
		for (int i = 1; i <= row_count; i++) {
			Multyply_Matrix_on_Row(i, B, sizes[i - 1], (point_mas + i - 1),
			(koef_mas_point + i - 1));
	}
	}
	int* res_sizes = new int[row_count + 1];
	res_sizes[0] = 0;
	for (int i = 1; i <= row_count; i++) {
		res_sizes[i] = res_sizes[i - 1] + sizes[i - 1];
	}
	T* res_value = new T[res_sizes[row_count]];
	int* res_koeff = new int[res_sizes[row_count]];
	int counter = 0;
	for (int i = 0; i < row_count; i++) {
		for (int j = 0; j < sizes[i]; j++) {
			res_value[counter] = point_mas[i][j];
			res_koeff[counter] = koef_mas_point[i][j];
			counter++;
		}
	}
	C->SetValue(res_sizes[row_count], res_value, res_koeff, res_sizes);
	return C;
}

template <typename T>
inline void
sparse_matrix<T>::SetValue(int _values_size, T* _values, int* _koeff,
	int* _lenghts)
{
	values_size = _values_size;
	values = new T[values_size];
	koeff = new int[values_size];
	for (int i = 0; i < values_size; i++) {
		values[i] = _values[i];
		koeff[i] = _koeff[i];
	}
	for (int i = 0; i <= row_count; i++) {
		lenghts[i] = _lenghts[i];
	}
}

template <typename T>
inline int
sparse_matrix<T>::Get_Row_Count()
{
	return row_count;
}

template <typename T>
inline int
sparse_matrix<T>::Get_Column_Count()
{
	return column_count;
}

template <typename T>
inline int
sparse_matrix<T>::Get_Size_Row(int k)
{
	return lenghts[k] - lenghts[k - 1];
}

template <typename T>
inline void
sparse_matrix<T>::Get_Row(int num, int& size_row, T** val_point,
	int** koeff_point)
{
	size_row = Get_Size_Row(num);
	*val_point = values + lenghts[num - 1];
	*koeff_point = koeff + lenghts[num - 1];
}

template <typename T>
inline void sparse_matrix<T>::Show()
{
	cout << "Values" << endl;
	for (int i = 0; i < values_size; i++)
	{
		cout << values[i] << " ";
		// cout << koeff[i] << endl; 
	}
	cout << endl;
	cout << "koef" << endl;
	for (int i = 0; i < values_size; i++)
	{
		cout << koeff[i] << " ";
		// cout << koeff[i] << endl; 
	}
	cout << endl;
	cout << "lenghts" << endl;
	for (int i = 0; i < row_count + 1; i++)
	{
		cout << lenghts[i] << " ";
	}
}

template <typename T>
inline void sparse_matrix<T>::crs_to_standart(complex<double> ** s_values)
{
	//T **s_values;
	//s_values = new T*[row_count];
	//for (int i = 0; i<row_count; i++)
	//{
	//	s_values[i] = new T[row_count]; 
	//}
	for (int i = 0; i < row_count; i++)
		for (int j = 0; j < row_count; j++)
		{
			s_values[i][j] = { 0,0 };
		}
	
	int p = 0;
	for (int i = 0; i < row_count; i++)
		for (int j = 0; j < values_size / row_count; j++)
		{
			s_values[i][koeff[p]] = values[p];
			p++;
		}
	cout << endl;
	cout << "=======================" << endl;
	for (int i = 0; i < row_count; i++)
	{
		for (int j = 0; j < row_count; j++)
		{
			cout << s_values[i][j] << " ";
		}
		cout << endl;
	}
	
}

template <typename T>
inline sparse_matrix<T>::~sparse_matrix()
{
	delete (values);
	delete (koeff);
	delete (lenghts);
}