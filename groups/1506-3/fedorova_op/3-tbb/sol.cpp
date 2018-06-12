#include <stdio.h>
#include "MyList.h"
#include <string>
#include <omp.h>

double max11(double r, cListl& list){
	double m;
	link prev = list[0];
	link current = list[1];
	double Max = abs((current.Getz() - prev.Getz()) / (current.Getx() - prev.Getx()));
	double Max1 = Max;
	for (int i = 0; i < list.get_count() - 2; i++)
	{
		Max = abs((current.Getz() - prev.Getz()) / (current.Getx() - prev.Getx()));
		if (Max > Max1)
			Max1 = Max;
		prev = current;
		current = list[list.get_number_on_x(prev.Getx()) + 1];
	}

	if (r > 1){
		if (Max1 > 0) m = r*Max1;
		if (Max1 = 0) m = 1;
	}
	return m;
}
