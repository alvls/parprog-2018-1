#include <ctime>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <string>
#include "MyList.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"

using namespace tbb;
using namespace std;

double calculation_functions(double x, int _funcNum);
double max11(double r, cListl& list); 

class my_range
{
private:
	double m_begin;
	double m_end;
	double m_grainsize;
public:
	my_range(const my_range& m)
	{
		m_begin = m.begin();
		m_end = m.end();
		m_grainsize = m.grainsize();
	}
	my_range(double begin, double end, double grainsize=1)
	{
		m_begin = begin;
		m_end = end;
		m_grainsize = grainsize;
	}
	my_range(my_range& m, split)
	{
		double new_begin, new_end;
		new_begin = m.begin() + m.grainsize();
		new_end = m.end();
		m_begin = new_begin;
		m_end = new_end;
		m_grainsize = m.grainsize();
		m.m_end = new_begin;
	}
	~my_range(){}
	double begin() const { return m_begin; }
	double end() const { return  m_end; }
	double grainsize() const { return m_grainsize; }
	bool is_divisible()
	{
		if ((m_end - m_begin) > m_grainsize + 0.00002)
			return true;
		else
			return false;
	}
	bool empty() const 
	{
		if (m_begin == m_end)
			return true;
		else
			return false;
	}


};


class myTbb
{
private:
	cListl* li;
	int funcNum, index_count;
	double parameter_r, epsilon;
	int nThreads;
public:
	explicit myTbb(int _funcNum, double _parameter_r, int _index_count, double _epsilon, int _nThreads)
	{
		li = new cListl(); 
		funcNum = _funcNum;
		index_count = _index_count;
		parameter_r = _parameter_r;
		epsilon = _epsilon;
	}

	myTbb(myTbb& m, split)
	{
		funcNum = m.funcNum;
		index_count = m.index_count;
		parameter_r = m.parameter_r;
		epsilon = m.epsilon;

		cListl* li = new cListl();		
	}
	
	void operator()( const my_range& r) {
		cListl* l = new cListl();
		l->Add(r.begin(), calculation_functions(r.begin(), funcNum));
		l->Add(r.end(), calculation_functions(r.end(), funcNum));
		cListl* l_r = new cListl();
		link prev, current;
		double Maxr;
		double m;
		double x = 0;
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

			prev = (*l)[l->get_number_on_x(((*l_r)[l_r->get_count() - 1]).Getz())];
			current = (*l)[l->get_number_on_x(prev.Getx()) + 1];
			x = 0.5*(current.Getx() + prev.Getx()) - (current.Getz() - prev.Getz()) / (2.0 * m); // не надо модуля. но с ним работает
			l->Add(x, calculation_functions(x, funcNum));

			if (abs(current.Getx() - prev.Getx()) <= epsilon){
				break;
			}
			l_r->del_cList();
		}
		li = l;

	}

	void join(const myTbb& rhs)
	{
		li->AddList(*rhs.li);
	}
	cListl* Result()
	{
		return li;
	}
};

int main(int argc, char* argv[])
{
	double parameter_r = 1.8, epsilon = 0.0001, a =-5, b = 5; // параметр, останов, интервал
	int funcNum = 5; // какая из функций
	double x = 0, x_glob = 0;
	int stepNum = 0;
	int nThreads = 4, curThread; // число потоков, текущий поток


	
	freopen("tests/50", "rb", stdin);
	FILE * f =freopen("tests/50.ans", "wb", stdout);
	fread(&funcNum, sizeof(funcNum), 1, stdin);
	fread(&a, sizeof(a), 1, stdin);
	fread(&b, sizeof(b), 1, stdin);
	fread(&epsilon, sizeof(epsilon), 1, stdin);
	fread(&parameter_r, sizeof(parameter_r), 1, stdin);
	

	int index_count = 5000;

	task_scheduler_init init(nThreads);
	auto t1 = tick_count::now();
	myTbb total(funcNum, parameter_r, index_count, epsilon, nThreads);
	parallel_reduce(my_range(a, b, (b - a) / nThreads) , total);
	cListl *l = new cListl(*total.Result());

	
	//находим минимальный элемент по y в списке, достаем минимальный х для него
	double min = (*l)[0].Getz();
	for (int i = 0; i < l->get_count(); i++){
		if (min >= (*l)[i].Getz()){
			min = (*l)[i].Getz();
			x_glob = (*l)[i].Getx();
		}
	}
	auto t2 = tick_count::now();
	auto time = (t2 - t1).seconds();
	double y_glob = calculation_functions(x_glob, funcNum);

	fwrite(&x_glob, sizeof(x_glob), 1, stdout);
	fwrite(&y_glob, sizeof(y_glob), 1, stdout);
	fwrite(&time, sizeof(time), 1, stdout);

	fclose(f);

	return 0;

}
