#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <conio.h>
#include <fstream>
#include <iostream>
#include "tbb_merge_sort.h"
#include <ctime>
#include "tbb/tick_count.h"
#include "tbb/task_scheduler_init.h"

int main(int argc, char * argv[])
{
	if (argc != 4) return 0;
	int count;
	double* values;
	int threads = 1;

	threads = atoi(argv[3]);
	task_scheduler_init init;

	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wb", stdout);

	fread(&count, sizeof(count), 1, stdin);

	values = new double[count];
	fread(values, sizeof(*values), count, stdin);

	init.initialize(threads);
	tick_count start = tick_count::now();
	ParallelSortDouble(values, count, threads);
	tick_count finish = tick_count::now();
	double time = (finish - start).seconds();

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&count, sizeof(count), 1, stdout);
	fwrite(values, sizeof(*values), count, stdout);
	return 0;
}