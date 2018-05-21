#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <ctime>
#include <omp.h>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

int get_max(vector<int>& array_for_sort, const int left_border, const int right_border);
void count_sort(vector<int>& array_for_sort, const int left_border, const int right_border, int digit);
void radix_sort_sol(vector<int>& array_for_sort, const int left_border, const int right_border);
void parallel_sort(vector<int>& vector_for_sorting, int _size, int _threads, double& _time);

int main(int argc, char * argv[])
{
	if (argc != 3) {
		if (argc != 4) {
		cout << "Enter the correct parameters:" << endl;
		cout << "1. The name of the source binary file" << endl;
		cout << "2. The name of the output binary file" << endl;
		cout << "3. The number of threads, type 2^n (if not, the default is a sequential version of the sort)" << endl;
		return 1;
		}
	}
	
	int size;
	double time=0;
	int threads = 0;
	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wb", stdout);
	if (argc == 4) {
		threads = atoi(argv[3]);
	}
	fread(&time, sizeof(time), 1, stdin);
	fread(&size, sizeof(size), 1, stdin);
	vector<int> check(size);
	int *arr = new int[size];
	fread(arr, sizeof(*arr), size, stdin);
	
	for (int i = 0; i < size; i++)
		check[i] = arr[i];

	if (threads==0) {
		time = omp_get_wtime();
		radix_sort_sol(check, 0, size - 1);
		time = omp_get_wtime() - time;
	}
	else { 
	parallel_sort(check, size, threads, time); }
	
	for (int i = 0; i < size; i++)
		arr[i] = check[i];
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(arr, sizeof(*arr), size, stdout);
	return 0;
}