#include <iostream> 
#include "sol.h"
#include <omp.h>
#include <random> 
#include <ctime> 
#include <chrono>
using namespace std;

void PlusArrSort(double * data, double * temp, int dataLength, int numOfByte) //сортировка положительных чисел по байту
{
	unsigned char* array = (unsigned char*)data;
	int counter[256];
	int offset;

	memset(counter, 0, sizeof(int) * 256);

	for (int i = 0; i < dataLength; i++)
		counter[array[8 * i + numOfByte]]++;

	// поиск номера состо€ни€ байта
	int j = 0;
	for (j; j < 256; j++)
		if (counter[j] != 0)
			break;

	offset = counter[j]; //число элементов с определенным байтом
	counter[j] = 0;
	j++;

	//подсчет смещений в итоговом массиве
	for (j; j < 256; j++)
	{
		int temp = counter[j];
		counter[j] = offset;
		offset += temp;
	}

	for (int i = 0; i < dataLength; i++)
	{
		temp[counter[array[8 * i + numOfByte]]] = data[i];// counter имеет всю информацию по сортировке элементов
		counter[array[8 * i + numOfByte]]++;
	}
}

void MinusArrSort(double * data, double * temp, int dataLength, int numOfByte) //сортировка отрицательных чисел по байту
{
	unsigned char* array = (unsigned char*)data;
	int counter[256];
	int offset;

	memset(counter, 0, sizeof(int) * 256);

	for (int i = 0; i < dataLength; i++)
	{
		counter[array[8 * i + numOfByte]]++;
	}

	int j = 255;
	for (j; j >= 0; j--)
		if (counter[j] != 0)
			break;

	offset = counter[j];
	counter[j] = 0;
	j--;

	for (j; j >= 0; j--)
	{
		int temp = counter[j];
		counter[j] = offset;
		offset += temp;
	}

	for (int i = 0; i < dataLength; i++)
	{
		temp[counter[array[8 * i + numOfByte]]] = data[i];
		counter[array[8 * i + numOfByte]]++;
	}
}

void RadixSort(double* data, int size) //поразр€дна€ сортировка
{
	double* arr_inp_plus;
	double* arr_inp_minus;
	double* arr_out_plus;
	double* arr_out_minus;
	int size_arr_plus = 0,
		size_arr_minus = 0;

	int counter_arr_plus = 0,
		counter_arr_minus = 0;

	for (int i = 0; i < size; i++)// ѕодсчитаем число положительных и отрицательных элементов
		if (data[i] > 0)
			size_arr_plus++;
		else
			size_arr_minus++;

	arr_inp_plus = new double[size_arr_plus];
	arr_inp_minus = new double[size_arr_minus];
	arr_out_plus = new double[size_arr_plus];
	arr_out_minus = new double[size_arr_minus];

	// –аскидаем + и - элементы в соответсвующие массивы
	for (int i = 0; i < size; i++)
		if (data[i] > 0)
			arr_inp_plus[counter_arr_plus++] = data[i];
		else
			arr_inp_minus[counter_arr_minus++] = data[i];

	// —ортируем положительный массив
	if (size_arr_plus > 0)
	{
		PlusArrSort(arr_inp_plus, arr_out_plus, size_arr_plus, 0);
		PlusArrSort(arr_out_plus, arr_inp_plus, size_arr_plus, 1);
		PlusArrSort(arr_inp_plus, arr_out_plus, size_arr_plus, 2);
		PlusArrSort(arr_out_plus, arr_inp_plus, size_arr_plus, 3);
		PlusArrSort(arr_inp_plus, arr_out_plus, size_arr_plus, 4);
		PlusArrSort(arr_out_plus, arr_inp_plus, size_arr_plus, 5);
		PlusArrSort(arr_inp_plus, arr_out_plus, size_arr_plus, 6);
		PlusArrSort(arr_out_plus, arr_inp_plus, size_arr_plus, 7);
	}

	// —ортирует отрицательный массив
	if (size_arr_minus > 0)
	{
		MinusArrSort(arr_inp_minus, arr_out_minus, size_arr_minus, 0);
		MinusArrSort(arr_out_minus, arr_inp_minus, size_arr_minus, 1);
		MinusArrSort(arr_inp_minus, arr_out_minus, size_arr_minus, 2);
		MinusArrSort(arr_out_minus, arr_inp_minus, size_arr_minus, 3);
		MinusArrSort(arr_inp_minus, arr_out_minus, size_arr_minus, 4);
		MinusArrSort(arr_out_minus, arr_inp_minus, size_arr_minus, 5);
		MinusArrSort(arr_inp_minus, arr_out_minus, size_arr_minus, 6);
		MinusArrSort(arr_out_minus, arr_inp_minus, size_arr_minus, 7);
	}

	// —ливаем
	for (int i = 0; i < size_arr_minus; i++)
		data[i] = arr_inp_minus[i];

	for (int i = 0; i < size_arr_plus; i++)
		data[i + size_arr_minus] = arr_inp_plus[i];

	delete[] arr_inp_minus;
	delete[] arr_inp_plus;
	delete[] arr_out_minus;
	delete[] arr_out_plus;

}

