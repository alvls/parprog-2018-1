#include <iostream> 

void PlusArrSort(double * data, double * sortedData, int dataLength, int numOfByte) //сортировка положительных чисел по байту
{
	unsigned char* array = (unsigned char*)data; 
	int counter[256];
	int offset;
	memset(counter, 0, sizeof(int) * 256);

	for (int i = 0; i < dataLength; i++)
		counter[array[8 * i + numOfByte]]++;

	// поиск номера состояния байта
	int i = 0;
	for (i; i < 256; i++)
		if (counter[i] != 0)
			break;

	offset = counter[i]; //число элементов с определенным байтом
	counter[i] = 0;
	i++;

	//подсчет смещений в итоговом массиве
	for (i; i < 256; i++)
	{
		int temp = counter[i];
		counter[i] = offset;
		offset += temp;
	}

	for (int i = 0; i < dataLength; i++)
	{
		sortedData[counter[array[8 * i + numOfByte]]] = data[i];// counter имеет всю информацию по сортировке элементов
		counter[array[8 * i + numOfByte]]++;
	}

}

void MinusArrSort(double * data, double * sortedData, int dataLength, int numOfByte) //сортировка отрицательных чисел по байту
{
	unsigned char* array = (unsigned char*)data;
	int counter[256];
	int offset;
	memset(counter, 0, sizeof(int) * 256);

	for (int i = 0; i < dataLength; i++)
	{
		counter[array[8 * i + numOfByte]]++;
	}

	int i = 255;
	for (i; i >= 0; i--)
		if (counter[i] != 0)
			break;

	offset = counter[i];
	counter[i] = 0;
	i--;

	for (i; i >= 0; i--)
	{
		int temp = counter[i];
		counter[i] = offset;
		offset += temp;
	}

	for (int i = 0; i < dataLength; i++)
	{
		sortedData[counter[array[8 * i + numOfByte]]] = data[i];
		counter[array[8 * i + numOfByte]]++;
	}
}

void RadixSort(double* data, int dataLength) //поразрядная сортировка
{
	int sizePlus = 0, sizeMinus = 0;
	for (int i = 0; i < dataLength; i++)
	{
		if (data[i] > 0)
			sizePlus++;
		else
			sizeMinus++;
	}

	double* firstArrP = new double[sizePlus];
	double* firstArrM = new double[sizeMinus];
	double* secondArrP = new double[sizePlus];
	double* secondArrM = new double[sizeMinus];

	//2 массива - с положительными и отрицательными элементами
	int j = 0, k = 0;
	for (int i = 0; i < dataLength; i++)
	{
		if (data[i] > 0)
			firstArrP[j++] = data[i];
		else
			firstArrM[k++] = data[i];
	}

	//сортировка по каждому байту
	if (sizePlus > 0)
	{
		PlusArrSort(firstArrP, secondArrP, sizePlus, 0);
		PlusArrSort(secondArrP, firstArrP, sizePlus, 1);
		PlusArrSort(firstArrP, secondArrP, sizePlus, 2);
		PlusArrSort(secondArrP, firstArrP, sizePlus, 3);
		PlusArrSort(firstArrP, secondArrP, sizePlus, 4);
		PlusArrSort(secondArrP, firstArrP, sizePlus, 5);
		PlusArrSort(firstArrP, secondArrP, sizePlus, 6);
		PlusArrSort(secondArrP, firstArrP, sizePlus, 7);
	}

	if (sizeMinus > 0)
	{
		MinusArrSort(firstArrM, secondArrM, sizeMinus, 0);
		MinusArrSort(secondArrM, firstArrM, sizeMinus, 1);
		MinusArrSort(firstArrM, secondArrM, sizeMinus, 2);
		MinusArrSort(secondArrM, firstArrM, sizeMinus, 3);
		MinusArrSort(firstArrM, secondArrM, sizeMinus, 4);
		MinusArrSort(secondArrM, firstArrM, sizeMinus, 5);
		MinusArrSort(firstArrM, secondArrM, sizeMinus, 6);
		MinusArrSort(secondArrM, firstArrM, sizeMinus, 7);
	}

	// объединение в итоговый массив
	for (int i = 0; i < sizeMinus; i++)
	{
		data[i] = firstArrM[i];
	}

	for (int i = 0; i < sizePlus; i++)
	{
		data[i + sizeMinus] = firstArrP[i];
	}
}

