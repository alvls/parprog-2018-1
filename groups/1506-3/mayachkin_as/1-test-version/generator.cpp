
#include "stdafx.h"
#include <fstream>
#include <random> 
#include <ctime> 
#include <chrono>
#include <omp.h>
#include <cstdio>
#include <string>

using namespace std;
int n_tests[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 500, 1000, 5000, 10000, 20000, 50000, 100000, 150000, 200000, 250000, 300000, 400000, 500000 };

int main(int argc, char * argv[])
{
	int n = 1;
	double* array;
	freopen("1", "wb", stdout);

	// ñîçäà¸ì ãåíåðàòîð ñëó÷àéíûõ ÷èñåë ñ seed ðàâíûì êîëè÷åñòâó âðåìåíè ñ íà÷àëà ýïîõè   
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	// ñîçäà¸ì ðàâíîìåðíîå ðàñïðåäåëåíèå ñëó÷àéíîé âåëè÷èíû òèïà double â äèàïàçîíå    
	//   [-10000, 10000]   
	uniform_real_distribution <double> distribution(-1e4, 1e4);
	int size = 10;
	// åñëè ïåðåäàëè íîìåð òåñòà â àðãóìåíòàõ êîìàíäíîé ñòðîêè, òî áåð¸ì ðàçìåð èç n_tests   
	if (argc > 1)
		size = n_tests[atoi(argv[1])];
	// çàïèñûâàåì â áèíàðíîì âèäå ðàçìåðíîñòü ìàòðèö   
	fwrite(&size, sizeof(size), 1, stdout);

	array = new double[size];

	for (int i = 0; i < size; i++)
		array[i] = distribution(generator);

	fwrite(array, sizeof(*array), size, stdout);

	delete[] array;
	return 0;
}
