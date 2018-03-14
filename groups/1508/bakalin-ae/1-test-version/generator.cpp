#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <random> 
#include <ctime> 
#include <chrono>
#include "point.h"

using namespace std;

int n_tests[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 80, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };

int main(int argc, char * argv[])
{
	freopen("points.in", "wb", stdout);
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	uniform_real_distribution <double> distribution(-1e4, 1e4);

	int size = 1000;

	if (argc > 1)
		size = n_tests[atoi(argv[1])];

	fwrite(&size, sizeof(size), 1, stdout);

	Point *arr = new Point[size];

	for (int i = 0; i < size; i++) {
		arr[i].x = distribution(generator);
		arr[i].y = distribution(generator);
	}

	fwrite(arr, sizeof(*arr), size, stdout);

	return 0;
}