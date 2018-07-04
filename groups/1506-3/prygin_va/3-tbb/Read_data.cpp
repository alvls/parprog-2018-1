#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <omp.h>
#include <random>
#include<iostream>
#include <fstream>
#include<conio.h>
#include<string>
#include <omp.h>
#include<tbb/task_scheduler_init.h>
#include<tbb/tick_count.h>

double MonteCarlo(double *functionValues, double leftBorderX, double leftBorderY, double rightBorderX, double rightBorderY, int N);

int main(int argc, char * argv[])
{
	int num_threads = 1;
	int testCount = 1;
	if (argc > 1)
	{
		num_threads = atoi(argv[1]);
	}
	if (argc > 2)
	{
		testCount = atoi(argv[2]);
	}

	for (int i = 0; i <= testCount; i++)
	{
		char index[10];
		int n = 0;

		double x1, x2, y1, y2;


		freopen(_itoa(i, index, 10), "rb", stdin);
		freopen(strcat(_itoa(i, index, 10), ".ans"), "wb", stdout);
		fread(&n, sizeof(n), 1, stdin);

		fread(&x1, sizeof(x1), 1, stdin);
		fread(&x2, sizeof(x2), 1, stdin);
		fread(&y1, sizeof(y1), 1, stdin);
		fread(&y2, sizeof(y2), 1, stdin);


		double *pFunctionValues = new double[n];

		fread(pFunctionValues, sizeof(*pFunctionValues), n, stdin);
		tbb::task_scheduler_init init(num_threads);
		tbb::tick_count timePar1 = tbb::tick_count::now();
		auto result = MonteCarlo(pFunctionValues, x1, y1, x2, y2, n);
		tbb::tick_count timePar2 = tbb::tick_count::now();
		double timePar = (timePar2 - timePar1).seconds;

		fwrite(&result, sizeof(result), 1, stdout);	
		fwrite(&timePar, sizeof(timePar), 1, stdout);

		fclose(stdout);
		fclose(stdin);
	}
	return 0;
}