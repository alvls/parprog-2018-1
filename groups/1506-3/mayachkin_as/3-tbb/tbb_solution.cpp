#include <iostream> 
#include <omp.h>
#include <random> 
#include <ctime> 
#include <chrono>
using namespace std;

#include "tbb/task_scheduler_init.h" 
#include "tbb/task.h" 
#include "tbb/parallel_for.h" 
#include "tbb/blocked_range.h" 
using namespace tbb;

void RadixSort(double* data, int dataLength);

class TBBEvenSplitter :public task
{
private:
	double* mas;
	double* tmp;
	int size1;
	int size2;

public:

	TBBEvenSplitter(double* data, double* temp, int size1_, int size2_) : mas(data), tmp(temp), size1(size1_), size2(size2_)
	{}

	task* execute()
	{
		for (int i = 0; i < size1; i += 2)
			tmp[i] = mas[i];

		double *mas2 = mas + size1;

		int a = 0;
		int b = 0;
		int i = 0;

		while ((a < size1) && (b < size2))
		{
			if (tmp[a] <= mas2[b])
			{
				mas[i] = tmp[a];
				a += 2;
			}
			else
			{
				mas[i] = mas2[b];
				b += 2;
			}

			i += 2;

		}

		if (a == size1)
			for (int j = b; j < size2; j += 2, i += 2)
				mas[i] = mas2[j];
		else
			for (int j = a; j < size1; j += 2, i += 2)
				mas[i] = tmp[j];

		return NULL;
	}

};

class TBBOddSplitter :public task
{
private:
	double* mas;
	double* tmp;
	int size1;
	int size2;

public:

	TBBOddSplitter(double* data, double* temp, int size1_, int size2_) : mas(data), tmp(temp), size1(size1_), size2(size2_)
	{}

	task* execute()
	{
		for (int i = 1; i < size1; i += 2)
			tmp[i] = mas[i];

		double *mas2 = mas + size1;

		int a = 1;
		int b = 1;
		int i = 1;

		while ((a < size1) && (b < size2))
		{
			if (tmp[a] <= mas2[b])
			{
				mas[i] = tmp[a];
				a += 2;
			}
			else
			{
				mas[i] = mas2[b];
				b += 2;
			}

			i += 2;
		}

		if (a == size1)
			for (int j = b; j < size2; j += 2, i += 2)
				mas[i] = mas2[j];
		else
			for (int j = a; j < size1; j += 2, i += 2)
				mas[i] = tmp[j];

		return NULL;
	}

};


class TBBSimpleComparator
{
private:
	double* mas;
	int size;

public:
	TBBSimpleComparator(double* data, int size) : mas(data), size(size)
	{}

	void operator()(const blocked_range<int>& r) const
	{
		int begin = r.begin(), end = r.end();

		for (int i = begin; i<end; i++)
			if (mas[2 * i] < mas[2 * i - 1])
			{
				double _tmp = mas[2 * i - 1];
				mas[2 * i - 1] = mas[2 * i];
				mas[2 * i] = _tmp;
			}
	}
};

class TBBParallelSorter :public task
{
private:
	double* mas;
	double* tmp;
	int size;
	int portion;

public:
	TBBParallelSorter(double* data, double* temp, int size_, int portion_) : mas(data), tmp(temp), size(size_), portion(portion_)
	{}

	task* execute()
	{
		if (size <= portion)
		{
			RadixSort(mas, size);
		}
		else
		{
			int s = size / 2 + (size / 2) % 2;

			TBBParallelSorter &sorter1 = *new (allocate_child()) TBBParallelSorter(mas, tmp, s, portion);
			TBBParallelSorter &sorter2 = *new (allocate_child()) TBBParallelSorter(mas + s, tmp + s, size - s, portion);

			set_ref_count(3);

			spawn(sorter1);
			spawn_and_wait_for_all(sorter2);

			TBBEvenSplitter &splitter1 = *new (allocate_child()) TBBEvenSplitter(mas, tmp, s, size - s);
			TBBOddSplitter &splitter2 = *new (allocate_child()) TBBOddSplitter(mas, tmp, s, size - s);

			set_ref_count(3);

			spawn(splitter1);
			spawn_and_wait_for_all(splitter2);

			parallel_for(blocked_range<int>(1, (size + 1) / 2), TBBSimpleComparator(mas, size));
		}

		return NULL;
	}
};

void TBBParallelSort(double *input, int size, int nThreads)
{
	double* out = new double[size];

	task_scheduler_init init(nThreads);

	int portion = size / nThreads;

	if (size%nThreads != 0)
		portion++;

	TBBParallelSorter& sorter = *new (task::allocate_root()) TBBParallelSorter(input, out, size, portion);
	task::spawn_root_and_wait(sorter);

	delete[] out;
}

