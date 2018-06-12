//Грибов П.Г. 381506-3. Поразрядная сортировка с простым слиянием. TBB версия.

#include <vector>
#include <algorithm>
#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/concurrent_vector.h"

using std::vector;
using namespace tbb;

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

// Поразрядная сортировка (последовательная)
void radix_sort(vector<int>& vec)
{
	// максимально возможное число разрядов в числе
	int max_dig_count = 10;
	// максимально возможное значение разряда числа (0..9)
	int max_dig = 10;
	// количество чисел
	int num_of_numbers = static_cast<int>(vec.size());
	// вспомогательные переменные и векторы
	int count, tmp;
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

/*************Сортировка с простым слиянием************/

using Iterator = vector<int>::iterator;

struct VecPart
{
	int start;
	int partsize;
	VecPart(int start_, int partsize_) : start(start_), partsize(partsize_) {}
};

concurrent_vector<VecPart> parts;

// Поразрядная сортировка части массива
void radix_sort_by(vector<int>& vec, const int& begin, const int& end, vector<int>& buffer)
{
	VecPart vp(begin, end - begin);
	parts.push_back(vp);

	if (end - begin == 1) return;

	// максимально возможное число разрядов в числе
	int max_dig_count = 10;
	// максимально возможное значение разряда числа (0..9)
	int max_dig = 10;
	// количество чисел
	int num_of_numbers = static_cast<int>(vec.size());
	// вспомогательные переменные и векторы
	int count, tmp;
	vector<int> pos_vec(10);

	for (int i = 0; i < max_dig_count; ++i)
	{
		for (int j = 0; j < max_dig; ++j)
			pos_vec[j] = 0;
		for (int j = begin; j < end; ++j)
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
		for (int j = begin; j < end; ++j)
		{
			buffer[begin + pos_vec[get_dig(vec[j], i)]++] = vec[j];
		}
		for (int j = begin; j < end; ++j)
		{
			vec[j] = buffer[j];
		}
	}

	int nneg = 0;

	for (int i = end - 1, j = begin; i >= begin; --i)
	{
		if (buffer[i] < 0)
		{
			++nneg;
			vec[j++] = buffer[i];
		}
	}
	for (int i = begin, j = begin + nneg; i < end; ++i)
	{
		if (buffer[i] >= 0)
		{
			vec[j++] = buffer[i];
		}
	}
}

void vec_merge(vector<int>& vec, const int& merge_num, const int& step, vector<int>& buffer)
{
	int current_part_num = merge_num * step * 2;

	if (current_part_num + step >= parts.size()) return;

	Iterator start1 = vec.begin() + parts[current_part_num].start; 
	Iterator finish1 = start1 + parts[current_part_num].partsize;
	Iterator start2 = finish1;
	Iterator finish2 = start2 + parts[current_part_num + step].partsize;
	Iterator buffer_start = buffer.begin() + parts[current_part_num].start;
	int count = static_cast<int>(std::distance(start1, finish2));

	while (start1 != finish1 && start2 != finish2)
		*buffer_start++ = *start1 <= *start2 ? *start1++ : *start2++;
	while (start1 != finish1)
		*buffer_start++ = *start1++;
	while (start2 != finish2)
		*buffer_start++ = *start2++;
	buffer_start = buffer.begin() + parts[current_part_num].start;
	start1 = vec.begin() + parts[current_part_num].start;
	for (int i = 0; i < count; ++i)
		*start1++ = *buffer_start++;
	parts[current_part_num].partsize += parts[current_part_num + step].partsize;
}

// Сортировка с простым слиянием (TBB)
void radix_sort_with_simple_merge(vector<int>& vec, int nthreads = 1)
{
	task_scheduler_init init(task_scheduler_init::deferred);

	int num_of_threads;
	if (nthreads > 1)
	{
		num_of_threads = nthreads;
		init.initialize(nthreads);
	}
	else
	{
		num_of_threads = task_scheduler_init::default_num_threads();
		init.initialize(num_of_threads);
	}

	int num_of_numbers = static_cast<int>(vec.size());
	int grainsize1 = num_of_numbers / num_of_threads;

	if (grainsize1 == 0)
	{
		radix_sort(vec);
		return;
	}

	vector<int> buffer(num_of_numbers);

	parallel_for(blocked_range<int>(0, num_of_numbers, grainsize1),
		[&vec, &buffer](const blocked_range<int>& r)
		{
			radix_sort_by(vec, r.begin(), r.end(), buffer);
		}, auto_partitioner()
	);
		
	std::sort(parts.begin(), parts.end(), [](const VecPart& vp1, const VecPart& vp2) { return vp1.start < vp2.start; });

	int parts_count = static_cast<int>(parts.size());
	
	for (int step = 1; step < parts_count; step *= 2)
	{
		parallel_for(blocked_range<int>(0, parts_count / 2),
			[&vec, &buffer, &num_of_numbers, &step](const blocked_range<int>& r)
			{
				int grainsize = r.grainsize();
				vec_merge(vec, r.begin(), step, buffer);
			}, auto_partitioner()
		);
	}
	
	if (num_of_threads >= 1)
		init.terminate();
}