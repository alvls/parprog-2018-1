#include <iostream> 
#include <omp.h>
#include <random> 
#include <ctime> 
#include <chrono>
using namespace std;

void RadixSort(double* data, int dataLength);

void  EvenSplitter(double* mas, double* tmp, int size1, int size2)
{
	for (int i = 0; i < size1; i += 2)
		tmp[i] = mas[i];

	double* mas2 = mas + size1;

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
}

void  OddSplitter(double* mas, double* tmp, int size1, int size2)
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
}

void SimpleComparator(double* mas, int size)
{
	for (int i = 1; i < (size + 1) / 2; i++)
		if (mas[2 * i] < mas[2 * i - 1])
		{
			double tmp = mas[2 * i - 1];
			mas[2 * i - 1] = mas[2 * i];
			mas[2 * i] = tmp;
		}
}

void Merge(double* mas, double* tmp, int size)
{

	int s = size / 2;

	EvenSplitter(mas, tmp, s, s);

	OddSplitter(mas, tmp, s, s);

	SimpleComparator(mas, size);

}

void ParallelSort(double* data, int size, int pnum)
{
	if (pnum == 1)
	{
		RadixSort(data, size);
	}
	else
	{
		double* tmp = new double[size];
		int part_size = size / pnum;
#pragma omp parallel shared(data, size, part_size, pnum, tmp) num_threads(pnum) 
		{
			int tid = omp_get_thread_num();
			int start = tid * part_size;
			RadixSort(data + start, part_size);
#pragma omp barrier 
			int level = pnum;
			int s = part_size;
			while (level != 1)
			{

				if (tid % 2 == 0 && tid < level)
				{
					EvenSplitter(data + tid * s, tmp + tid * s, s, s);
				}
				if (tid % 2 == 1 && tid < level)
				{
					int t = tid - 1;
					OddSplitter(data + t * s, tmp + tid * s, s, s);
				}
#pragma omp barrier 
				if (tid % 2 == 0 && tid < level)
				{
					SimpleComparator(data + tid * s, s * 2);
				}
#pragma omp barrier 
				level /= 2;
				s *= 2;
			}
		}
		delete[] tmp;
	}
}

