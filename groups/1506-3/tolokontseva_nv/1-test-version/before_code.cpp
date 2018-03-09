
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio> //io
#include <cstdlib> //atoi
#include <chrono>		 /*time measurements*/
typedef std::chrono::high_resolution_clock::time_point TimeVar;
#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

void radix_sort(double *arr, double* res, int size);

int main(int argc, char* argv[]) {
	/*args: input file name, output file name, number of threads*/
	if (argc < 3) {
		printf("Expected name of input and output files! Exiting...");
		return 1;
	}

	int size; //size of array
	double *arr, //array
		   *res; //sorted array

	//freopen redirect file to the stream
	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wb", stdout);

	//read size of array
	fread(&size, sizeof(size), 1, stdin);

	//allocate memory for array before and after sort
	arr = new double[size];
	res = new double[size];

	//read array
	fread(arr, sizeof(*arr), size, stdin);

	TimeVar t1;
	double time;
	t1 = timeNow();
	//sort array. Result of sort is written in res
	radix_sort(arr, res, size);
	time = duration(timeNow() - t1);

	//write to the result file size of array, time of sort, sorted array
	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(res, sizeof(*res), size, stdout);

	//free allocated memory
	delete[]arr;
	delete[]res;
	return 0;
};