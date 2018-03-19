#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;


int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "Enter [output.bin] [output.txt] " << endl;
		return 1;
	}
	double time;
	int* arr;
	int size;

	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wt", stdout);

	fread(&time, sizeof(double), 1, stdin);
	fread(&size, sizeof(int), 1, stdin);

	arr = new int[size];

	fread(arr, sizeof(*arr), size, stdin);

	for (int i = 0; i < size; i++)
		cout << arr[i] << endl;

	return 0;
}
