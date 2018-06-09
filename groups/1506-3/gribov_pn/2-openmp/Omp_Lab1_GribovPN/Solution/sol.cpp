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

/*********************Вариант №1***********************/
/************Сортировка без простого слияния***********/

// Поразрядная сортировка
void radix_sort(vector<int>& vec, int num_of_threads = 1)
{
	int max_dig_count = 10;
	int max_dig = 10;
	int num_of_numbers = static_cast<int>(vec.size());

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

/*********************Вариант №2***********************/
/*************Сортировка с простым слиянием************/

// Поразрядная сортировка части массива
void radix_sort_by(vector<int>& vec, int begin, int end, vector<int>& buffer)
{
    if (end - begin == 1) return;
    // максимально возможное число разрядов в числе
    int max_dig_count = 10;
    // максимально возможное значение разряда числа (0..9)
    int max_dig = 10;
    // количество чисел
    int num_of_numbers = static_cast<int>(vec.size());
    // вспомогательные переменные и векторы
    int count, tmp;
    //vector<int> buffer(num_of_numbers);
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

void vec_merge(vector<int>& vec, const int& begin1, const int& end1,
    const int& begin2, const int& end2, vector<int>& buffer)
{
    vector<int>::iterator start1 = vec.begin() + begin1;
    vector<int>::iterator finish1 = vec.begin() + end1;
    vector<int>::iterator start2 = vec.begin() + begin2;
    vector<int>::iterator finish2 = vec.begin() + end2;
    vector<int>::iterator buffer_start = buffer.begin() + begin1;
    int count = end2 - begin1;

    while (start1 != finish1 && start2 != finish2)
        *buffer_start++ = *start1 <= *start2 ? *start1++ : *start2++;
    while (start1 != finish1)
        *buffer_start++ = *start1++;
    while (start2 != finish2)
        *buffer_start++ = *start2++;
    buffer_start = buffer.begin() + begin1;
    start1 = vec.begin() + begin1;
    for (int i = 0; i < count; ++i)
        *start1++ = *buffer_start++;

}

void radix_sort_with_simple_merge(vector<int>& vec, int nthreads = 1)
{
    if (nthreads > 1)
        omp_set_num_threads(nthreads);

    int num_of_numbers = static_cast<int>(vec.size());

    vector<int> buffer(num_of_numbers);

    #pragma omp parallel shared(buffer, num_of_numbers)
    {
        int num_of_threads = omp_get_num_threads();
        int bucket_size = num_of_numbers / num_of_threads;
        if (bucket_size != 0 && bucket_size != 1)
        {
            int tid = omp_get_thread_num();
            int begin = tid * bucket_size;
            int end;

            if (tid == num_of_threads - 1)
                end = num_of_numbers;
            else end = begin + bucket_size;

            radix_sort_by(vec, begin, end, buffer);
            #pragma omp barrier

            if (num_of_threads > 1)
            {
                for (int size = bucket_size; size < num_of_numbers; size *= 2)
                {
                    int begin1 = 2 * tid * size;
                    int end1 = begin1 + size;
                    int begin2 = end1;
                    int end2 = begin2 + size;
                    if (abs(num_of_numbers - end2) > 0 && abs(num_of_numbers - end2) < size)
                        end2 = num_of_numbers;
                    if (end2 <= num_of_numbers)
                        vec_merge(vec, begin1, end1, begin2, end2, buffer);
                    #pragma omp barrier
                }
            }
        }
        else
        {
            #pragma omp single
            {
                radix_sort_by(vec, 0, num_of_numbers, buffer);
            }
        }
    }
}
