#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio> 
#include <random> 
#include <ctime> 
#include <chrono>
#include "point.h"

using namespace std;

int n_tests[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 100, 200, 500, 1000, 2000, 5000, 10000, 15000, 20000, 25000, 50000, 100000,
				500000, 800000, 1000000, 1500000};

int main(int argc, char * argv[])
{
	if (argc < 2) {
		std::cout << "GENERATOR PROGRAM\n" << "To use this program, please stick to the following pattern:\n" <<
			"generator [number of test(0-32)] ... [number of test(0-32)]" << std::endl;
		return 1;
	}

	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	uniform_real_distribution <double> distribution(-1e3, 1e3);

	for (int i = 1; i < argc; i++) {

		int size = n_tests[atoi(argv[i])];

		freopen(argv[i], "wb", stdout);
		fwrite(&size, sizeof(size), 1, stdout);

		Point *arr = new Point[size];

		for (int i = 0; i < size; i++) {
			arr[i].x = distribution(generator);
			arr[i].y = distribution(generator);
		}

		fwrite(arr, sizeof(*arr), size, stdout);
	}

	return 0;
}