
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
int makeListofMins(cListl* l, cListl* l_r, int funcNum, double parameter_r, double epsilon);

int main(int argc, char* argv[])
{
	double parameter_r = 2, epsilon = 0.0001, a =-10, b =10; // параметр, останов, интервал
	int funcNum = 2; // какая из функций
	double x = 0, x_glob = 0;
	int stepNum=0;
	
	freopen("tests/10", "rb", stdin);
	FILE * f =freopen("tests/10.ans", "wb", stdout);
	fread(&funcNum, sizeof(funcNum), 1, stdin);
	fread(&a, sizeof(a), 1, stdin);
	fread(&b, sizeof(b), 1, stdin);
	fread(&epsilon, sizeof(epsilon), 1, stdin);
	fread(&parameter_r, sizeof(parameter_r), 1, stdin);
	
	cListl *l = new cListl();
	cListl *l_r = new cListl();

	l->Add(a, calculation_functions(a, funcNum));
	l->Add(b, calculation_functions(b, funcNum));

	
	double t1=0,t2=0;
	
	t1 = omp_get_wtime();

	stepNum = makeListofMins(l, l_r, funcNum, parameter_r, epsilon);
	
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
