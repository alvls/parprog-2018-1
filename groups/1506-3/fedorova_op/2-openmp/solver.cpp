
#include <ctime>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <string>
#include "MyList.h"
#include <omp.h>
using namespace std;

double calculation_functions(double x, int _funcNum);
double max11(double r, cListl& list); 

int main(int argc, char* argv[])
{
	double parameter_r = 1.8, epsilon = 0.0001, a =2.7,b =7.5; // параметр, останов, интервал
	int funcNum = 0; // какая из функций
	double x = 0, x_glob = 0;
	int stepNum=0;
	double t1 = 0, t2 = 0; // время
	int nThreads = 4, curThread; // число потоков, текущий поток
	omp_set_num_threads(nThreads); 

	
	freopen("tests/1", "rb", stdin);
	FILE * f =freopen("tests/1.ans", "wb", stdout);
	fread(&funcNum, sizeof(funcNum), 1, stdin);
	fread(&a, sizeof(a), 1, stdin);
	fread(&b, sizeof(b), 1, stdin);
	fread(&epsilon, sizeof(epsilon), 1, stdin);
	fread(&parameter_r, sizeof(parameter_r), 1, stdin);
	
	cListl *l = new cListl();
	cListl *new_mas, *l_r;

	int index_count = 5000;
	double m = 1;
	link prev;
	link current;
	double Maxr;
	int i, j;
	int numstep = 0;
	int stepmas[16] = { 0 };

	t1 = omp_get_wtime();
#pragma omp parallel shared  (l, funcNum,a,b,parameter_r, epsilon, nThreads, index_count) private(numstep,l_r, curThread, new_mas, stepNum,prev , current, Maxr, j,m) // что надо здесь добавить???
	{
		nThreads = omp_get_num_threads();
		new_mas = new cListl();
		l_r = new cListl();
			curThread = omp_get_thread_num();
			if (curThread == 0)
			{
				new_mas->Add(a, calculation_functions(a, funcNum));
				new_mas->Add(a + abs(b - a) / nThreads, calculation_functions(a + abs(b - a) / nThreads, funcNum));
			}
			else if (curThread == (nThreads - 1))
			{
				new_mas->Add(a + curThread*(abs(a - b) / nThreads), calculation_functions(a + curThread*(abs(a - b) / nThreads), funcNum));
				new_mas->Add(b, calculation_functions(b, funcNum));
			}
			else
			{
				new_mas->Add(a + curThread*(abs(a - b) / nThreads), calculation_functions(a + curThread*(abs(a - b) / nThreads), funcNum));
				new_mas->Add(a + (curThread + 1) * (abs(a - b) / nThreads), calculation_functions(a + (curThread + 1) * (abs(a - b) / nThreads), funcNum));
			}


			for (i = 0; i < index_count; i++)
			{
				m = max11(parameter_r, *new_mas);
					for (j = 0; j < (*new_mas).get_count() - 1; j++)
					{
						prev = (*new_mas)[j];
						current = (*new_mas)[j + 1];
						Maxr = m*(current.Getx() - prev.Getx()) + (pow((current.Getz() - prev.Getz()), 2)) / (m*(current.Getx() - prev.Getx()))
							- 2.0 * (current.Getz() + prev.Getz());
						l_r->Add(Maxr, prev.Getx());
					}
				
					numstep++;
				prev = (*new_mas)[new_mas->get_number_on_x(((*l_r)[l_r->get_count() - 1]).Getz())];
				current = (*new_mas)[new_mas->get_number_on_x(prev.Getx()) + 1];
				x = 0.5*(current.Getx() + prev.Getx()) - (current.Getz() - prev.Getz()) / (2.0 * m); // не надо модуля. но с ним работает
				new_mas->Add(x, calculation_functions(x, funcNum));

				if (abs(current.Getx() - prev.Getx()) <= epsilon){
					break;
				}
				l_r->del_cList();
				stepmas[curThread] = numstep;
			}

#pragma omp critical
			{
				l->AddList(*new_mas);
			}		

	}
	
	//находим минимальный элемент по y в списке, достаем минимальный х для него
	double min = (*l)[0].Getz();
	for (int i = 0; i < l->get_count(); i++){
		if (min >= (*l)[i].Getz()){
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

}
