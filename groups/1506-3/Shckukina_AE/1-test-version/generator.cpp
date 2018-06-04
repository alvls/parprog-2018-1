#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <random> 
#include <ctime> 
#include <chrono>
#include <iostream>

using namespace std;

int n_tests[] = { 1, 2, 3, 5, 7, 8, 10, 100, 500, 1000, 5000, 10000, 10000, 500000, 100000, 1000000, 10000000, 25000000, 50000000, 100000000 };

int main(int argc, char * argv[])
{
	if (atoi(argv[1]) < 1 || atoi(argv[1]) > 20 || argc != 2)
	{
		cout << "Error! You should input 1-20" << endl;
		return 1;
	}
	int n = n_tests[atoi(argv[1]) - 1]; //count of elements in vector/array

	string name = argv[1];
	string type = ".bin";
	name += type;
	freopen(name.c_str(), "wb", stdout);

	default_random_engine generator(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
	uniform_real_distribution <double> distribution(0, 1000);

	fwrite(&n, sizeof(double), 1, stdout);
	fwrite(&n, sizeof(n), 1, stdout);

	double* array = new double[n];

	for (int i = 0; i < n; i++) {
		array[i] = distribution(generator);
	}

	fwrite(array, sizeof(*array), n, stdout);
	return 0;
}


