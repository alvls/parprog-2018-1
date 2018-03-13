#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <random>
#include <ctime>
#include <iostream>

void QuickSort(int* arr, int size);

int main(int argc, char * argv[])
{
	if (argc != 3) {
		std::cout << "Use 'solver [input file] [output file]'" << std::endl;
		return 1;
	}

	int size;
	int* arr;

	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wb", stdout);

	fread(&size, sizeof(size), 1, stdin);
	
	arr = new int[size];
	fread(arr, sizeof(*arr), size, stdin);

	unsigned int start_time = clock();
	QuickSort(arr, size);
	unsigned int duration = clock() - start_time;

	fwrite(&duration, sizeof(duration), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(arr, sizeof(*arr), size, stdout);
	return 0;
}