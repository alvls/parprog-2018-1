// Чтение данных и точка входа в программу
#include <cstdio>
#include <string>
#include <omp.h>

void radix_sort(vector<int>& vec);

int main(int argc, char * argv[])
{
	int N;

	std::vector<int> vec;

	if (argc <= 1)
	{
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

	double time = omp_get_wtime();
	radix_sort(vec);
	time = omp_get_wtime() - time;

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&N, sizeof(N), 1, stdout);
	fwrite(vec.data(), sizeof(int), N, stdout);

	fclose(stdout);
	fclose(stdin);
}