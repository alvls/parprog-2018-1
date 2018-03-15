#include "Stack.h"


void quickSort(dot* arr, int startInd, int endInd)
{
	if (startInd < endInd)
	{
		dot pivot = arr[startInd];
		int middleInd = startInd;
		for (auto i = startInd + 1; i < endInd; i++)
			if (arr[i] < pivot)
			{
				middleInd++;
				std::swap(arr[middleInd], arr[i]);
			}
		std::swap(arr[startInd], arr[middleInd]);
		quickSort(arr, startInd, middleInd);
		quickSort(arr, middleInd + 1, endInd);
	}
}

void quickSortSearchMin(dot* arr, int startInd, int endInd)
{
	if (startInd < endInd)
	{
		dot pivot = arr[startInd];
		int middleInd = startInd;
		for (auto i = startInd + 1; i < endInd; i++)
			if ((arr[i].x < pivot.x) || ((arr[i].x == pivot.x) && (arr[i].y < pivot.y)))
			{
				middleInd++;
				std::swap(arr[middleInd], arr[i]);
			}
		std::swap(arr[startInd], arr[middleInd]);
		quickSortSearchMin(arr, startInd, middleInd);
		quickSortSearchMin(arr, middleInd + 1, endInd);
	}
}

void searchMinElement(dot* dotArray, int size)
{
	quickSortSearchMin(dotArray, 0, size);
}

/*
void searchMinElement(dot* dotArray, int size)
{
	for (int i = 1; i < size; i++)
	{
		if ((dotArray[i].x < dotArray[0].x) || ((dotArray[i].x == dotArray[0].x) && (dotArray[i].y < dotArray[0].y)))
			std::swap(dotArray[0], dotArray[i]);
	}
}*/

std::pair<dot*, int> grehemMethod(dot* dotArray, int size)
{
	searchMinElement(dotArray, size - 1);
	dot move = dotArray[0];
	for (auto i = 0; i < size - 1; i++)
		dotArray[i] = dotArray[i] - move;
	quickSort(dotArray, 1, size - 1);
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
	{
		resultArray[i] = resultArray[i] + move;
	}
	return std::make_pair(resultArray, dotStack.getSize());
}

