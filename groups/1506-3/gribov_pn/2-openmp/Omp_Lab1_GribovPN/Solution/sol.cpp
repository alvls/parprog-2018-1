//Грибов П.Г. 381506-3. Поразрядная сортировка с простым слиянием. OpenMP версия.

#include <vector>
#include <algorithm>
#include <omp.h>

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
void radix_sort(vector<int>& vec, int num_of_threads = 1)
{
	int max_dig_count = 10;
	int max_dig = 10;
	int num_of_numbers = static_cast<int>(vec.size());
	int dig, count, tmp;
	vector<int> buffer(num_of_numbers);
	vector<int> local_pos_vec(10);
	vector<int> pos_vec(10);

	if (num_of_threads > 1)
		omp_set_num_threads(num_of_threads);

	for (int i = 0; i < max_dig_count; ++i)
	{
		for (int j = 0; j < max_dig; ++j)
		{
			local_pos_vec[j] = 0;
			pos_vec[j] = 0;
		}
		#pragma omp parallel firstprivate(local_pos_vec)
		{
			#pragma omp for schedule(static) nowait
			for (int j = 0; j < num_of_numbers; ++j)
			{
				++local_pos_vec[get_dig(vec[j], i)];
			}
			#pragma omp critical
			for (int j = 0; j < max_dig; ++j)
			{
				pos_vec[j] += local_pos_vec[j];
			}
			/*count = 0;
			for (int j = 0; j < max_dig; ++j)
			{
			tmp = pos_vec[j];
			pos_vec[j] = count;
			count += tmp;
			}*/
			#pragma omp barrier

			#pragma omp single
			{
				for (int j = 1; j < max_dig; ++j)
				{
					pos_vec[j] += pos_vec[j - 1];
				}
			}
			int nthreads = omp_get_num_threads();
			int tid = omp_get_thread_num();
			for (int j = nthreads - 1; j >= 0; --j)
			{
				if (j == tid)
				{
					for (int k = 0; k < max_dig; ++k)
					{
						pos_vec[k] -= local_pos_vec[k];
						local_pos_vec[k] = pos_vec[k];
					}
				}
				else
				{
					#pragma omp barrier
				}
			}
			#pragma omp for schedule(static)
			for (int j = 0; j < num_of_numbers; ++j)
			{
				buffer[local_pos_vec[get_dig(vec[j], i)]++] = vec[j];
			}
			vec = buffer;
		}
	}
	vec.clear();
	std::copy_if(buffer.rbegin(), buffer.rend(), std::back_inserter(vec), [](int i) { return i < 0; });
	std::copy_if(buffer.begin(), buffer.end(), std::back_inserter(vec), [](int i) { return i >= 0; });
}
