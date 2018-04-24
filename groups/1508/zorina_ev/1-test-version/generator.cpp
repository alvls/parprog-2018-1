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
	uniform_int_distribution <int> distribution(0, 100000);

	fwrite(0, sizeof(double), 1, stdout);	//фиктивное время
	fwrite(&n, sizeof(int), 1, stdout);

	int* array = new int[n];

	for (int i = 0; i < n; i++) 
	{
		array[i] = distribution(generator);
	}

	fwrite(array, sizeof(*array), n, stdout);
	return 0;
}



