#include <stdio.h>
#include "MyList.h"
#include <string>
double calculation_functions(double x, int _funcNum);
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

int makeListofMins(cListl* l, cListl* l_r, int funcNum, double parameter_r, double epsilon)
{
	int index_count = 5000;
	double x = 0;
	double m = 1;
	link prev;
	link current;
	int stepNum = 0;
	double Maxr;
	for (int i = 0; i < index_count; i++)
	{
		m = max11(parameter_r, *l);
		for (int j = 0; j < (*l).get_count() - 1; j++)
		{
			prev = (*l)[j];
			current = (*l)[j + 1];
			Maxr = m*(current.Getx() - prev.Getx()) + (pow((current.Getz() - prev.Getz()), 2)) / (m*(current.Getx() - prev.Getx()))
				- 2.0 * (current.Getz() + prev.Getz());
			l_r->Add(Maxr, prev.Getx());
		}
		stepNum++;
		prev = (*l)[l->get_number_on_x(((*l_r)[l_r->get_count() - 1]).Getz())];
		current = (*l)[l->get_number_on_x(prev.Getx()) + 1];
		x = 0.5*(current.Getx() + prev.Getx()) - (current.Getz() - prev.Getz()) / (2.0 * m);
		l->Add(x, calculation_functions(x, funcNum));

		if (abs(current.Getx() - prev.Getx()) <= epsilon){
			break;
		}
		l_r->del_cList();
	}
	return stepNum;
}

