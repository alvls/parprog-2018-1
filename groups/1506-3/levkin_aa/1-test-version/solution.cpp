#include "solution.h"

template<typename Tmass, typename Tint> void split(Tmass* mass, Tint iStart, Tint iFinish, Tint halfSizeMass) 
{
	Tmass *massTemp = new Tmass[iFinish - iStart + 1];
	for (Tint i = 0; i < halfSizeMass; i++) 
	{
		massTemp[i] = mass[iStart + 2 * i];
		massTemp[i + halfSizeMass] = mass[iStart + 2 * i + 1];
	}

	for (Tint i = iStart; i < iFinish; i++)
		mass[i] = massTemp[i - iStart];

	delete[]massTemp;
}

template<typename Tmass, typename Tint> void unsplit(Tmass* mass, Tint iStart, Tint iFinish, Tint halfSizeMass) 
{
	Tmass *massTemp = new Tmass[iFinish - iStart + 1];
	for (Tint i = 0; i < halfSizeMass; i++) {
		massTemp[2 * i] = mass[iStart + i];
		massTemp[2 * i + 1] = mass[iStart + i + halfSizeMass];
	}
	for (Tint i = iStart; i < iFinish; i++) 
		mass[i] = massTemp[i - iStart];

	delete[]massTemp;
}

template<typename T> void swapMaxMin(T& x1, T& x2)
{
	if (x1>x2)
	{
		T tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
}

template<typename Tmass, typename Tint> void mergeMass(Tmass* mass, Tint iStart, Tint iFinish) 
{
	Tint halfSizeMass = (iFinish - iStart) / 2;
	if ((iFinish - iStart) > 2) 
	{
		split(mass, iStart, iFinish, halfSizeMass);
		mergeMass(mass, iStart, iStart + halfSizeMass);
		mergeMass(mass, iStart + halfSizeMass, iFinish);
		unsplit(mass, iStart, iFinish, halfSizeMass);

		for (Tint i = iStart + 1; i < iFinish - 1; i += 2)
			swapMaxMin(mass[i], mass[i + 1]);
	}
	else 
		swapMaxMin(mass[iStart], mass[iStart + 1]);
}


template<typename Tmass, typename Tint> void qsortBatcher(Tmass* mass, Tint iStart, Tint iFinish) 
{
	if ((iFinish - iStart) > 1) 
	{
		Tint halfSizeMass = (iFinish - iStart) / 2;
		qsortBatcher(mass, iStart, iStart + halfSizeMass);
		qsortBatcher(mass, iStart + halfSizeMass, iFinish);
		mergeMass(mass, iStart, iFinish);
	}
}


void qsortBatcher(int* mass, int size)
{
	qsortBatcher(mass, 0, size);
}
