//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <vector>
//using namespace std;
//
//int main(int argc, char * argv[])
//{
//	if (argc != 3) {
//		cout << "Use 'viewer [input file] [output file]'" << endl;
//		return 1;
//	}
//
//	int size;
//	double* arr;
//	double time;
//
//	freopen(argv[1], "rb", stdin);
//	freopen(argv[2], "wt", stdout);
//
//	fread(&time, sizeof(time), 1, stdin); //переменная под время
//	fread(&size, sizeof(size), 1, stdin);
//	arr = new double[size];
//	fread(arr, sizeof(*arr), size, stdin);
//
//	for (int i = 0; i < size; ++i)
//		cout << arr[i] << endl;
//	return 0;
//}
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 3) {
		cout << "You input incorrect number of arguments. Input 'viewer file.bin file.txt'" << endl;
		return 1;
	}

	int size;
	double* arr;
	double time;

	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "wt", stdout);

	fread(&time, sizeof(time), 1, stdin);
	//fwrite(&time, sizeof(time), 1, stdout); //output time in sort binary
	fread(&size, sizeof(size), 1, stdin);
	arr = new double[size];
	vector <double> vec(size);
	for (int i = 0; i < size; i++) {
		fread(&vec[i], sizeof(double), 1, stdin);
		cout << vec[i] << endl;
	}
	return 0;
}