#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <ctime>
#include <omp.h>
#include <iostream>
#include <vector>
using namespace std;

//void shuffle(vector<int>& array_for_sort, const int left_border, const int right_border);
//void unshuffle(vector<int>& array_for_sort, const int left_border, const int right_border);
int get_max(vector<int>& array_for_sort, const int left_border, const int right_border);
void count_sort(vector<int>& array_for_sort, const int left_border, const int right_border, int digit);
void radix_sort_sol(vector<int>& array_for_sort, const int left_border, const int right_border);

int main(int argc, char * argv[])
{
	if (argc != 3) {
		cout << "You use a serial version of the algorithm. Enter the arguments in the correct format !!" << endl;
		return 1;
	}
	
	int size;
	double time=0;
	
	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wb", stdout);

	fread(&time, sizeof(time), 1, stdin);
	fread(&size, sizeof(size), 1, stdin);
	vector<int> check(size);
	fread(check.data(), sizeof(check), size, stdin);

	time = omp_get_wtime();
	radix_sort_sol(check,0,size-1);
	time = omp_get_wtime() - time;

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(check.data(), sizeof(int), size, stdout);
	return 0;
}