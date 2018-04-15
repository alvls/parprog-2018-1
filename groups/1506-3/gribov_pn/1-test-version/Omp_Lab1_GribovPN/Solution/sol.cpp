//Грибов П.Г. 381506-3. Поразрядная сортировка с простым слиянием. Последовательная версия.

#include <vector>
#include <algorithm>

using std::vector;

// Функция получения требуемого разряда числа
int get_dig(int num, int dig_num)
{
	num = abs(num);
	for (int i = 0; i < (dig_num - 1); ++i)
	{
		num /= 10;
	}
	return num % 10;
}

// Поразрядная сортировка (Алгоритм №2)
void radix_sort(vector<int>& vec)
{
	int max_dig_count = 10;
	int max_dig = 10;
	int num_of_numbers = static_cast<int>(vec.size());
	int count, tmp;
	int num_threads = 4;
	vector<int> buffer(num_of_numbers);
	vector<int> pos_vec(10);

	for (int i = 0; i < max_dig_count; ++i)
	{
		for (int j = 0; j < max_dig; ++j)
			pos_vec[j] = 0;
		for (int j = 0; j < num_of_numbers; ++j)
		{
			++pos_vec[get_dig(vec[j], i)];
		}
		count = 0;
		for (int j = 0; j < max_dig; ++j)
		{
			tmp = pos_vec[j];
			pos_vec[j] = count;
			count += tmp;
		}
		for (int j = 0; j < num_of_numbers; ++j)
		{
			buffer[pos_vec[get_dig(vec[j], i)]++] = vec[j];
		}
		vec = buffer;
	}
	vec.clear();
	std::copy_if(buffer.rbegin(), buffer.rend(), std::back_inserter(vec), [](int i) { return i < 0; });
	std::copy_if(buffer.begin(), buffer.end(), std::back_inserter(vec), [](int i) { return i >= 0; });
}