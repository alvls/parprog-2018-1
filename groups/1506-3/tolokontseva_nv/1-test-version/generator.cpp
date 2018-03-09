#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <random>
#include <ctime>
#include <algorithm>
#include <limits>
#include <chrono>		 /*time measurements*/
typedef std::chrono::high_resolution_clock::time_point TimeVar;
#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

using namespace std;

int n_tests[] = { 1, 1000, 1000, 1000, 1000,
				  10, 50, 100, 500, 500,
				  1000, 5000, 5000, 5000, 10000,
				  10000, 10000, 50000, 50000, 50000,
				  100000, 100000, 100000, 500000, 500000};
/* special cases:
already sorted array;
sorted inversivly array;
array with duplicates;
array where every element has the same value*/
enum specific
{
	random, sorted, sorted_inv, duplicates, single_value
};

specific test_variant[] = { random, sorted, sorted_inv, duplicates, single_value,
							random, random, random, random, random,
							random, random, random, random, random,
							random, random, random, random, random,
							random, random, random, random, random };

void generate_random(double *arr, int n) {
	// create random number generator, seed is set to the time since the epoch begin
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());

	// create uniform distribution of double, numbers are between -10000 and 10000
	uniform_real_distribution <double> distribution(-1e4, 1e4);

	for (int i = 0; i < n; i++) {
		arr[i] = distribution(generator);
	}
}

void generate_sorted(double *arr, int n) {
	//first element is always -200
	//there may appear error if n is too high, but I suppose it's 1000
	//by too high I mean (-200 + n*0.4 exceed max double value)
	arr[0] = -200;
	double step = 0.4;
	for (int i = 1; i < n; i++) {
		arr[i] = arr[i - 1] + step;
	}
}

void generate_sorted_inv(double *arr, int n) {
	//principe is the same as in generate_sorted
	arr[n - 1] = -200;
	double step = 0.4;
	for (int i = n - 2; i >	-1; i--) {
		arr[i] = arr[i + 1] + step;
	}
}

void generate_single_value(double *arr, int n) {
	// create random number generator, seed is set to the time since the epoch begin
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	// create uniform distribution of double, numbers are between -10000 and 10000
	uniform_real_distribution <double> distribution(-1e4, 1e4);
	double value = distribution(generator);
	for (int i = 0; i < n; i++) {
		arr[i] = value;
	}
}

void generate_duplicated(double *arr, int n) {
	// create random number generator, seed is set to the time since the epoch begin
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());

	// create uniform distribution of double, numbers are between -10000 and 10000
	uniform_real_distribution <double> u_distribution(-1e4, 1e4);

	//create bernoulli distribution;
	// give "true" 1/10 of the time
	// give "false" 9/10 of the time
	std::bernoulli_distribution d(0.1);
	arr[0] = u_distribution(generator);;
	for (int i = 1; i < n; i++) {
		if (d(generator)) {
			arr[i] = arr[i - 1];
		}
		else {
			arr[i] = u_distribution(generator);
		}
	}

}


int main(int argc, char * argv[]) {
	char f_name[100] = "arr.in";
	if (argc > 1) {
		if (argv[1] == "help") {
			printf("Possible parameters: <file name> <test number> [<ans file name>]");
			return 0;
		}
		//redirect stdout to the file with given name
		freopen(argv[1], "wb", stdout);
	}
	else {
		// redirect stdo to the "arr.in"
		freopen("arr.in", "wb", stdout);
	}


	// array size
	int n = 10;
	//way to fill in the array
	specific test_v = random;

	// read test number if passed
	if (argc > 2) {
		n = n_tests[atoi(argv[1])];
		test_v = test_variant[atoi(argv[1])];
	}

	// write array size to binary file
	fwrite(&n, sizeof(n), 1, stdout);

	// allocate memory for the array
	double * arr = new double[n];

	// generate array
	switch (test_v)
	{
	case random:
		generate_random(arr, n);
		break;
	case sorted:
		generate_sorted(arr, n);
		break;
	case sorted_inv:
		generate_sorted_inv(arr, n);
		break;
	case single_value:
		generate_single_value(arr, n);
		break;
	case duplicates:
		generate_duplicated(arr, n);
		break;
	default:
		generate_random(arr, n);
	}

	// write array to binary file
	fwrite(arr, sizeof(*arr), n, stdout);


	// create "ans" file
	if (argc > 3) {
		FILE *f = NULL;
		TimeVar t1;
		double time;
		//name of file is taken from paramets
		f = fopen(argv[3], "wb");

		t1 = timeNow();

		//sort array with STL function
		sort(arr, arr + n);

		time = duration(timeNow() - t1);

		// write array size to binary file
		fwrite(&n, sizeof(n), 1, f);
		//write time of sort to binary file
		fwrite(&time, sizeof(time), 1, f);
		//write sorted array to binary file
		fwrite(arr, sizeof(*arr), n, f);
		fclose(f);
	}
	return 0;
}