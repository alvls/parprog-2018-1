
#include <ctime>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <string>
#include <omp.h>
#include "MyList.h"
using namespace std;
double calculation_functions(double x, int _funcNum);

void makeListofMins(cListl* l, cListl* l_r, int funcNum)
{
	int index_count = 10000;
	double x = 0;
	link prev;
	link current;
	double Maxr;
	for (int i = 0; i < index_count; i++)
	{
		for (int j = 0; j < (*l).get_count() - 1; j++)
		{
			prev = (*l)[j];
			current = (*l)[j + 1];
			Maxr = current.Getx() - prev.Getx();
			l_r->Add(Maxr, prev.Getx());
		}
		prev = (*l)[l->get_number_on_x(((*l_r)[l_r->get_count() - 1]).Getz())];
		current = (*l)[l->get_number_on_x(prev.Getx())+1];
		x = (current.Getx() + prev.Getx()) / 2.0;
		l->Add(x, calculation_functions(x, funcNum));

		l_r->del_cList();
	}
}

int main(int argc, char* argv[])
{
	//for (int k = 7; k < 70; k++){
		double a = 2.7, b = 7.5; //  интервал
		int funcNum = 0; // какая из функций

		freopen("tests/1", "rb", stdin);
		FILE * f = freopen("etalon.out", "wb", stdout);
		fread(&funcNum, sizeof(funcNum), 1, stdin);
		fread(&a, sizeof(a), 1, stdin);
		fread(&b, sizeof(b), 1, stdin);

		double x = 0, x_glob = 0;

		cListl *l = new cListl();
		cListl *l_r = new cListl();

		l->Add(a, calculation_functions(a, funcNum));
		l->Add(b, calculation_functions(b, funcNum));

		double t1 = 0, t2 = 0;
		t1 = omp_get_wtime();
		makeListofMins(l, l_r, funcNum);

		//находим минимальный элемент по y в списке, достаем минимальный х для него
		double min = (*l)[0].Getz();
		for (int i = 0; i < l->get_count(); i++){
			if (min >(*l)[i].Getz()){
				min = (*l)[i].Getz();
				x_glob = (*l)[i].Getx();
			}
		}
		t2 = omp_get_wtime();
		double time = t2 - t1;
		double y_glob = calculation_functions(x_glob, funcNum);

		fwrite(&x_glob, sizeof(x_glob), 1, stdout);
		fwrite(&y_glob, sizeof(y_glob), 1, stdout);
		fwrite(&time, sizeof(time), 1, stdout);

		fclose(f);
		return 0;
	//}

}
