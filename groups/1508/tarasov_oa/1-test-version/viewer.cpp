#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 3) {
		cout << "Use 'viewer [input file] [output file]'" << endl;
		return 1;
	}

	int size;
	int* arr;
	double time;

	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wt", stdout);

	fread(&time, sizeof(time), 1, stdin);
	fread(&size, sizeof(size), 1, stdin);
	arr = new int[size];
	fread(arr, sizeof(*arr), size, stdin);

	for (int i = 0; i < size; ++i)
		cout << arr[i] << endl;
	return 0;
}
