#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 3) {
		cout << "You use the \"Viewer\" to process data. Enter the arguments in the correct format !!" << endl;
		return 1;
	}
	int size;
	double real_time;
	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wt", stdout);

	fread(&real_time, sizeof(real_time), 1, stdin);
	fread(&size, sizeof(size), 1, stdin);
	cout <<real_time << endl;
	vector<int> check(size);
	fread(check.data(), sizeof(check), size, stdin);
	for (int i = 0; i < size; ++i)
		cout << check[i] << endl;
	return 0;
}