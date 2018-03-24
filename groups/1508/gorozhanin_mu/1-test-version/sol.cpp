//Горожанин М.Ю. 381508. Поразрядная сортировка для целых чисел с четно-нечетным слиянием Бэтчера. Алгоритм сортировки.
#pragma once

#include <vector>
#include <queue>

using namespace std;
///
///Shuffle — Четно-нечетное разбиения Бэтчера. 
///Делим массив пополам и далее первый элемент первой половины — первый в результате, первый элемент второй половины — второй в результате, второй первой половины — третий в результате и т.д.
///Массив обязательно четной длины.Фактически, мы расставляем элементы первой половины по четным позициям, а из второй — по нечетной.
///
void shuffle(vector<int>& array_for_sort, const int left_border, const int right_border)
{
	const int half = (left_border + right_border) / 2;
	vector<int> tmp(array_for_sort.size());
	int i, j;
	if ((left_border + right_border) % 2 == 0) {
		tmp[right_border] = array_for_sort[half];
		for (i = left_border, j = 0; i < right_border; i += 2, j++)
		{
			tmp[i] = array_for_sort[left_border + j];
			tmp[i + 1] = array_for_sort[half + j + 1];
		}
		for (i = 0; i < tmp.size(); i++)
			array_for_sort[i] = tmp[i];
	}
	else {
		for (i = left_border, j = 0; i <= right_border; i += 2, j++)
		{
			tmp[i] = array_for_sort[left_border + j];
			tmp[i + 1] = array_for_sort[half + j + 1];
		}
		for (i = 0; i < tmp.size(); i++)
			array_for_sort[i] = tmp[i];
	}
}

///
///Unshuffle — Четно-нечетное слияние Бэтчера. 
///Операция обратная предыдущей.
///Элементы, занимающие четные позиции, отправляются в первую половину массива - результата, нечетные — во вторую.
///
void unshuffle(vector<int>& array_for_sort, const int left_border, const int right_border)
{
	const int half = (left_border + right_border) / 2;
	vector<int> tmp(array_for_sort.size());
	int i, j;
	if ((left_border + right_border) % 2 == 0) {
		tmp[half] = array_for_sort[right_border];
		for (i = left_border, j = 0; i < right_border; i += 2, j++)
		{
			tmp[left_border + j] = array_for_sort[i];
			tmp[half + j + 1] = array_for_sort[i + 1];
		}
		for (i = 0; i < tmp.size(); i++)
			array_for_sort[i] = tmp[i];
	}
	else {
		for (i = left_border, j = 0; i <= right_border; i += 2, j++)
		{
			tmp[left_border + j] = array_for_sort[i];
			tmp[half + j + 1] = array_for_sort[i + 1];
		}
		for (i = 0; i < tmp.size(); i++)
			array_for_sort[i] = tmp[i];
	}
}

///
/// Получаем максимальное значение из массива. 
///
int get_max(vector<int>& array_for_sort, const int left_border, const int right_border)
{
	int max = array_for_sort[left_border];
	for (int i = 1; i <= right_border; i++)
		if (abs(array_for_sort[i]) > max)
			max = array_for_sort[i];
	return max;
}
///
/// Процесс сортировки массива по выделенному разряду.
///
void count_sort(vector<int>& array_for_sort, const int left_border, const int right_border, int digit)
{
	vector<int> output(right_border - left_border + 1);
	int count[10] = { 0 };
	//for (int i = right_border; i <= left_border; i--)
	//	output[i] = 0;

	for (int i = left_border; i <= right_border; i++)
		count[(abs(array_for_sort[i]) / digit) % 10]++;

	for (int i = 1; i <10; i++)
		count[i] += count[i - 1];

	for (int i = right_border; i >= left_border; i--)
	{
		output[count[(abs(array_for_sort[i]) / digit) % 10] - 1] = array_for_sort[i];
		count[(abs(array_for_sort[i]) / digit) % 10]--;
	}

	for (int i = left_border; i <= right_border; i++)
		array_for_sort[i] = output[i];
}

void radix_sort_sol(vector<int>& array_for_sort, const int left_border, const int right_border)
{
	auto num_of_numbers = array_for_sort.size();
	vector<int> vec_pos;
	vector<int> vec_neg;

	auto num_of_pos_numbers = 0;
	auto num_of_neg_numbers = 0;

	for (size_t i = 0; i < num_of_numbers; ++i)
		if (array_for_sort[i] >= 0)
			num_of_pos_numbers++;

	num_of_neg_numbers = num_of_numbers - num_of_pos_numbers;

	vec_pos.reserve(num_of_pos_numbers);
	vec_neg.reserve(num_of_neg_numbers);

	copy_if(array_for_sort.begin(), array_for_sort.end(), back_inserter(vec_pos), [](int i) { return i >= 0; });
	copy_if(array_for_sort.begin(), array_for_sort.end(), back_inserter(vec_neg), [](int i) { return i < 0; });
	
	const int max_elem = get_max(array_for_sort, left_border, right_border);
	for (int curr_digit = 1; max_elem / curr_digit > 0; curr_digit *= 10)
		count_sort(vec_pos, 0, num_of_pos_numbers-1, curr_digit);
	for (int curr_digit = 1; max_elem / curr_digit > 0; curr_digit *= 10)
		count_sort(vec_neg, 0, num_of_neg_numbers-1, curr_digit);
	reverse(vec_neg.begin(), vec_neg.end());
	array_for_sort.clear();
	copy(vec_neg.begin(), vec_neg.end(), back_inserter(array_for_sort));
	copy(vec_pos.begin(), vec_pos.end(), back_inserter(array_for_sort));
}