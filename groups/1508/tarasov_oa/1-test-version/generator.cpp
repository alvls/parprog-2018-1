#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <random> 
#include <ctime> 
#include <chrono>

using namespace std;

int n_tests[] = { 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };

int main(int argc, char * argv[])
{
	freopen("array.in", "wb", stdout);
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution <int> distribution(0, 1000);
	int N = 1000;
	if (argc > 1)
		N = n_tests[atoi(argv[1])];
	fwrite(&N, sizeof(N), 1, stdout);

	int *arr = new int[N];
	for (int i = 0; i < N; i++) 
		arr[i] = distribution(generator);
	fwrite(arr, sizeof(*arr), N, stdout);
	return 0;
}