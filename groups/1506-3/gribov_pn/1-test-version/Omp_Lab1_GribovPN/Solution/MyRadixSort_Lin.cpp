//Грибов П.Г. 381506-3. Поразрядная сортировка с простым слиянием. Последовательная версия. MyRadixSort_Lin.cpp
#include "MyRadixSort_Lin.h"

//функция получения требуемого разряда числа
int get_dig(int num, int dig_num)
{
	num = abs(num);
	for (size_t i = 0; i < (dig_num - 1); ++i)
	{
		num /= 10;
	}
	return num % 10;
}

//поразрядная сортировка
void radix_sort(vector<int>& vec)
{
	//максимальное количество разрядов сортируемых чисел
	size_t max_num_of_dig = 1;
	
	//количество сортируемых чисел
	size_t num_of_numbers = vec.size();
	
	//вектор положительных чисел
	vector<int> pvec;
	//вектор отрицательных чисел
	vector<int> nvec;
	//количество положительных чисел
	size_t num_of_p_numbers = 0;
	//количество отрицательных чисел
	size_t num_of_n_numbers = 0;

	for (size_t i = 0; i < num_of_numbers; ++i)
		if (vec[i] >= 0)
			++num_of_p_numbers;

	num_of_n_numbers = num_of_numbers - num_of_p_numbers;

	pvec.reserve(num_of_p_numbers);
	nvec.reserve(num_of_n_numbers);

	//вектор очередей
	vector<queue<int>> vec_of_queue(10);
	
	//вычисление макс. кол-ва разрядов
	int max_number = (*std::max_element(vec.begin(), vec.end(), [](int x, int y) { return (y < 0 ? y : -y) < (x < 0 ? x : -x); } ));
	while (max_number /= 10)
		++max_num_of_dig;
	
	//isSorted - флаг проверки отсортированности для досрочного завершения
	bool isSorted = false;
	
	for (size_t i = 0; i < max_num_of_dig && !isSorted; ++i)
	{
		isSorted = true;
		for (size_t j = 0; j < num_of_numbers; ++j)
		{
			vec_of_queue[get_dig(vec[j],i+1)].push(vec[j]);
		}
		for (size_t j = 0, k = 0, l = 0; j < 10; ++j)
		{
			while (!vec_of_queue[j].empty())
			{
				vec[k++] = vec_of_queue[j].front();
				vec_of_queue[j].pop();
			}
		}
		for (size_t j = 0; j < (num_of_numbers - 1) && isSorted; ++j)
		{
			if(abs(vec[j]) > abs(vec[j+1]))
				isSorted = false;
		}
	}

	std::copy_if(vec.begin(), vec.end(), std::back_inserter(pvec), [](int i) { return i >= 0; });
	std::copy_if(vec.begin(), vec.end(), std::back_inserter(nvec), [](int i) { return i < 0; });
	std::reverse(nvec.begin(), nvec.end());
	vec.clear();
	std::copy(nvec.begin(), nvec.end(), std::back_inserter(vec));
	std::copy(pvec.begin(), pvec.end(), std::back_inserter(vec));
}