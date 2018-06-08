//Горожанин М.Ю. 381508. Поразрядная сортировка для целых чисел с четно-нечетным слиянием Бэтчера. Алгоритм сортировки.
#pragma once

#include <vector>
#include <queue>

using namespace std;

///
/// Получаем максимальное значение из массива. 
///
int get_max(vector<int>& array_for_sort, const int left_border, const int right_border)
{
	int max = abs(array_for_sort[left_border]);
	for (int i = left_border; i <= right_border; i++)
		if (abs(array_for_sort[i]) > max)
			max = abs(array_for_sort[i]);
	return max;
}
///
/// Процесс сортировки массива по выделенному разряду.
///
void count_sort(vector<int>& array_for_sort, const int left_border, const int right_border, int digit)
{
	vector<int> output(right_border - left_border + 1);
	int count[10] = { 0 };
	
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
	auto num_of_numbers = right_border-left_border+1;
	vector<int> vec_pos;
	vector<int> vec_neg;

	auto num_of_pos_numbers = 0;
	auto num_of_neg_numbers = 0;

	for (size_t i = left_border; i < right_border+1; ++i)
		if (array_for_sort[i] >= 0)
			num_of_pos_numbers++;

	num_of_neg_numbers = num_of_numbers - num_of_pos_numbers;

	vec_pos.reserve(num_of_pos_numbers);
	vec_neg.reserve(num_of_neg_numbers);
	vector<int> temp = array_for_sort;
	vector<int>::iterator it_chunk_begin, it_chunk_end;
	it_chunk_begin = temp.begin() + left_border;
	it_chunk_end = temp.begin() + left_border + num_of_numbers;
	copy_if(it_chunk_begin, it_chunk_end, back_inserter(vec_pos), [](int i) { return i >= 0; });
	copy_if(it_chunk_begin, it_chunk_end, back_inserter(vec_neg), [](int i) { return i < 0; });
	
	const int max_elem = get_max(temp, left_border, right_border);
	for (int curr_digit = 1; max_elem / curr_digit > 0; curr_digit *= 10)
		count_sort(vec_pos, 0, num_of_pos_numbers-1, curr_digit);
	for (int curr_digit = 1; max_elem / curr_digit > 0; curr_digit *= 10)
		count_sort(vec_neg, 0, num_of_neg_numbers-1, curr_digit);
	reverse(vec_neg.begin(), vec_neg.end());
	
	for (int i = left_border,j=0; i < left_border + num_of_neg_numbers; i++,j++)
		array_for_sort[i] = vec_neg[j];
	for (int i = left_border+num_of_neg_numbers, j = 0; i < right_border+1; i++, j++)
		array_for_sort[i] = vec_pos[j];
}