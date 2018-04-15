// Программа для правильной сортировки
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <omp.h>

int main(int argc, char * argv[])
{
	int N;

	std::vector<int> vec;

	if (argc <= 1)
	{
		//freopen("test.in", "rb", stdin);
		//freopen("test.out", "wb", stdout);
		return 0;
	}
	else
	{
		freopen((".\\tests\\" + std::string(argv[1])).c_str(), "rb", stdin);
		freopen((".\\tests\\" + std::string(argv[1]) + "_true.ans").c_str(), "wb", stdout);
	}

	fseek(stdin, sizeof(double), SEEK_SET); // пропуск фиктивного времени
	fread(&N, sizeof(N), 1, stdin);

	vec.resize(N);

	fread(vec.data(), sizeof(int), N, stdin);

	double time = omp_get_wtime();
	std::sort(vec.begin(), vec.end());
	time = omp_get_wtime() - time;

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&N, sizeof(N), 1, stdout);
	fwrite(vec.data(), sizeof(int), N, stdout);

	fclose(stdout);
	fclose(stdin);
}
