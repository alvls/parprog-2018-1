// Чтение данных и точка входа в программу
#include <cstdio>
#include <string>
#include <vector>
#include "tbb/tick_count.h"
#include "tbb/concurrent_vector.h"

// прототипы функций
int get_dig(int num, int dig_num);
//void radix_sort(std::vector<int>& vec);
void radix_sort_with_simple_merge(std::vector<int>& vec, int nthreads = 1);

int main(int argc, char * argv[])
{
	int N;

	std::vector<int> vec;

	if (argc <= 1)
	{
		printf("Few arguments, it must be:\nsolution.exe [test_number] [number_of_threads=auto]");
		return 0;
	}
	else
	{
		freopen((".\\tests\\" + std::string(argv[1])).c_str(), "rb", stdin);
		freopen((".\\tests\\" + std::string(argv[1]) + ".ans").c_str(), "wb", stdout);
	}

	fseek(stdin, sizeof(double), SEEK_SET); // пропуск фиктивного времени
	fread(&N, sizeof(N), 1, stdin);

	vec.resize(N);

	fread(vec.data(), sizeof(int), N, stdin);

	tbb::tick_count start = tbb::tick_count::now();
	if(argc == 2)
		radix_sort_with_simple_merge(vec);
	else radix_sort_with_simple_merge(vec, atoi(argv[2]));
	tbb::tick_count finish = tbb::tick_count::now();

	double time = (finish - start).seconds();

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&N, sizeof(N), 1, stdout);
	fwrite(vec.data(), sizeof(int), N, stdout);

	fclose(stdout);
	fclose(stdin);
}
