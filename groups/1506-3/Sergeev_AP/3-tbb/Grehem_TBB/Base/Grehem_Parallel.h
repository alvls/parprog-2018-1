#include "Stack.h"
#include <iostream>
#include "task_scheduler_init.h" 
#include "task.h"

using namespace tbb;

class SortTask: public task
{
	dot* dotArray;
	int startInd;
	int endInd;

public:

	SortTask(dot* arr, int stInd, int enInd): dotArray(arr), startInd(stInd), endInd(enInd)
	{ }

	task* execute()
	{
		if (startInd < endInd)
		{
			dot pivot = dotArray[startInd];
			int middleInd = startInd;
			for (auto i = startInd + 1; i < endInd; i++)
				if (dotArray[i] < pivot)
				{
					middleInd++;
					std::swap(dotArray[middleInd], dotArray[i]);
				}
			std::swap(dotArray[startInd], dotArray[middleInd]);

			set_ref_count(3);
			SortTask& sortUp = *new (allocate_child()) SortTask(dotArray, startInd, middleInd);
			SortTask& sortDown = *new (allocate_child()) SortTask(dotArray, middleInd + 1, endInd);
			spawn(sortUp);
			spawn_and_wait_for_all(sortDown);
		}
		else
			return NULL;
	}
};

class SortMinTask : public task
{
	dot* dotArray;
	int startInd;
	int endInd;

public:

	SortMinTask(dot* arr, int stInd, int enInd) : dotArray(arr), startInd(stInd), endInd(enInd)
	{ }

	task* execute()
	{
		if (startInd < endInd)
		{
			dot pivot = dotArray[startInd];
			int middleInd = startInd;
			for (auto i = startInd + 1; i < endInd; i++)
				if ((dotArray[i].x < pivot.x) || ((dotArray[i].x == pivot.x) && (dotArray[i].y < pivot.y)))
				{
					middleInd++;
					std::swap(dotArray[middleInd], dotArray[i]);
				}
			std::swap(dotArray[startInd], dotArray[middleInd]);

			set_ref_count(3);
			SortMinTask& sortUp = *new (allocate_child()) SortMinTask(dotArray, startInd, middleInd);
			SortMinTask& sortDown = *new (allocate_child()) SortMinTask(dotArray, middleInd + 1, endInd);
			spawn(sortUp);
			spawn_and_wait_for_all(sortDown);
		}
		else
			return NULL;
	}
};

void sortParallel(dot* arr, int startInd, int endInd, int numThreads)
{	
	SortTask& sortT = *new (task::allocate_root()) SortTask(arr, startInd, endInd);
	task::spawn_root_and_wait(sortT);
}

void searchMinElement(dot* dotArray, int size, int numThreads)
{
	SortMinTask& sortMin = *new (task::allocate_root()) SortMinTask(dotArray, 0, size);
	task::spawn_root_and_wait(sortMin);
}

std::pair<dot*, int> grehemMethod_TBB(dot* dotArray, int size, int numThreads)
{
	tbb::task_scheduler_init init(numThreads);

	searchMinElement(dotArray, size - 1, numThreads);
	dot move = dotArray[0];
	for (auto i = 0; i < size - 1; i++)
		dotArray[i] = dotArray[i] - move;

	sortParallel(dotArray, 1, size - 1, numThreads);
	dotArray[size - 1] = dotArray[0];
	stack dotStack(size / 2);
	dot dotY, dotX;
	dotStack.push(dotArray[0]);
	dotStack.push(dotArray[1]);
	for (auto i = 2; i < size; i++)
	{
		while (true)
		{
			if (dotStack.getSize() > 1)
			{
				dotY = dotStack.pop();
				dotX = dotStack.get();
				if ((dotArray[i].x*(dotX.y - dotY.y) + dotArray[i].y*(dotY.x - dotX.x) + dotX.x*dotY.y - dotX.y*dotY.x) > 0)
				{
					dotStack.push(dotY);
					dotStack.push(dotArray[i]);
					break;
				}
				else
				{
					if (dotStack.getSize() == 1)
					{
						dotStack.push(dotArray[i]);
						break;
					}
				}
			}
		}
	}
	dot* resultArray = dotStack.getArray();
	for (auto i = 0; i < dotStack.getSize(); i++)
		resultArray[i] = resultArray[i] + move;
	return std::make_pair(resultArray, dotStack.getSize());
}

