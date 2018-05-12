#include  "Dot.h"

class stack
{
	int size;
	int maxSize;
	dot* Array;
public:
	stack(int inSize)
	{
		size = 0;
		maxSize = inSize;
		Array = new dot[maxSize];
	}

	~stack()
	{
		delete[] Array;
	}

	void copy(dot* copiedArr, dot* pasteArr, int size)
	{
		for (auto i = 0; i < size; i++)
			pasteArr[i] = copiedArr[i];
	}

	void push(dot& element)
	{
		if (size + 1 == maxSize)
		{
			dot* tmpArr = Array;
			Array = new dot[maxSize * 2];
			copy(tmpArr, Array, maxSize);
			maxSize = maxSize * 2;
			delete[] tmpArr;
		}
		Array[size] = element;
		size++;
	}

	dot get()
	{
		return Array[size - 1];
	}

	dot pop()
	{
		size--;
		return Array[size];
	}

	int getSize()
	{
		return size;
	}

	dot* getArray()
	{
		dot* retArray = new dot[size];
		copy(Array, retArray, size);
		return retArray;
	}
};