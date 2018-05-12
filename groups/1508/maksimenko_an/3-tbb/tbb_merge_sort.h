#include "tbb/task.h"
using namespace std;
using namespace tbb;

class ParallelSorter :public task
{
private:
	double *values;
	double *add;
	int count;
	int portion;

	void Split(int size1, int size2)
	{
		for (int i = 0; i < size1; i++)
			add[i] = values[i];

		double *values2 = values + size1;

		int a = 0;
		int b = 0;
		int i = 0;

		while ((a != size1) && (b != size2))
		{
			if (add[a] <= values2[b])
			{
				values[i] = add[a];
				a++;
			}
			else
			{
				values[i] = values2[b];
				b++;
			}
			i++;
		}
			if (a == size1)
				for (int j = b; j<size2; j++)
					values[size1 + j] = values2[j];
			else
				for (int j = a; j<size1; j++)
					values[size2 + j] = add[j];
	}

	void SortDouble(double* values, double* add, int count)
	{
		if (count == 1)
			return;
		else
			if (count == 2) {
				if (values[0] > values[1])
					swap(values[0], values[1]);
				return;
			}
		int m = count / 2;
		SortDouble(values, add, m);
		SortDouble(values + m, add + m, count - m);

		int a = 0;
		int b = m;
		int j = 0;

		while ((a != m) && (b != count))
		{
			if (values[a] > values[b])
			{
				add[j] = values[b];
				b++;
			}
			else
			{
				add[j] = values[a];
				a++;
			}
			j++;
		}
		if (a == m)
			for (int i = b; i < count; i++)
			{
				add[j] = values[i];
				j++;
			}
		else
		{
			for (int i = a; i < m; i++)
			{
				add[j] = values[i];
				j++;
			}
		}
		for (int i = 0; i < count; i++)
			values[i] = add[i];
	}
public:
	ParallelSorter(double* _values, double* _add, int _count, int _portion) : values(_values), add(_add), count(_count), portion(_portion)
	{}

	task* execute()
	{
		if (count <= portion)
		{
			SortDouble(values, add, count);
		}
		else
		{
			ParallelSorter &sorter1 = *new(allocate_child())ParallelSorter(values, add, count / 2, portion);
			ParallelSorter &sorter2 = *new(allocate_child())ParallelSorter(values + count / 2, add + count / 2, count - count / 2, portion);
			set_ref_count(3);

			spawn(sorter1);
			spawn_and_wait_for_all(sorter2);

			Split(count / 2, count - count / 2);
		}
		return NULL;
	}
};

void ParallelSortDouble(double *mas, int count, int nThreads)
{
	double *temp = new double[count];

	int portion = count / nThreads;

	if (count%nThreads != 0)
		portion++;

	ParallelSorter& sorter = *new(task::allocate_root())ParallelSorter(mas, temp, count, portion);
	
	task::spawn_root_and_wait(sorter);

	delete[] temp;
}