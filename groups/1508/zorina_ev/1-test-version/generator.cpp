/*#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include <iostream>
using namespace std;

int  n_tests[] = { 1, 2, 5, 10, 10, 20, 50, 100, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000, 2000000, 5000000, 10000000};


int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "please, enter ' generator [number_test] [output.bin] ' " << endl;
		return 1;
	}

	int n = n_tests[atoi(argv[1] - 1)];

	freopen(argv[2], "wb", stdout);
	default_random_engine generator(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
	uniform_int_distribution <int> distribution(0, 100000);

	//fwrite(&n, sizeof(double), 1, stdout); //фиктивное время
	fwrite(&n, sizeof(n), 1, stdout);
	int *cur = new int[n];

	for(int i = 0; i < n; i++)
		cur[i] = distribution(generator);

	fwrite(cur, sizeof(*cur), n, stdout);
	return 0;
}*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <random> 
#include <ctime> 
#include <chrono>
#include <iostream>

using namespace std;

int n_tests[] = { 1, 2, 3, 4, 6, 8, 10, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000, 50000000, 100000000 };

int main(int argc, char * argv[])
{
	if ( argc != 2)
	{
		cout << "Enter number from 1 to 20" << endl;
		return 1;
	}

	int n = n_tests[atoi(argv[1]) - 1]; 

	string name = argv[1];
	string type = ".bin";
	name += type;
	freopen(name.c_str(), "wb", stdout);

	default_random_engine generator(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
	uniform_real_distribution <double> distribution(0, 100000);

	fwrite(&n, sizeof(double), 1, stdout);
	fwrite(&n, sizeof(n), 1, stdout);

	double* array = new double[n];

	for (int i = 0; i < n; i++) 
	{
		array[i] = distribution(generator);
	}

	fwrite(array, sizeof(*array), n, stdout);
	return 0;
}



