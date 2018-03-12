#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <chrono>
#include <iostream>
#include <random>
#include "math.h"
using namespace std;

//void q_Sort(vector <double> arr)
//{
//	int first = 0;
//	int last = arr.size()- 1;
//	int elem = arr[arr.size() / 2];
//
//	do {
//		while (arr[first] < elem) 
//			first++;
//		while (arr[last] > elem) 
//			last--;
//
//		if (first <= last) {
//			int tmp = arr[first];
//			arr[first] = arr[last];
//			arr[last] = tmp;
//			first++;
//			last--;
//		}
//	} while (first <= last);
//
//	cout << "*" << endl;
//	if (last > 0) {
//		vector<double>vec1(arr.begin(), arr.begin() + last+1);
//		q_Sort(vec1);
//	}
//	cout << "@" << endl;
//	if (first < arr.size())
//	{
//		vector<double>vec2(arr.begin()+first, arr.end());
//		q_Sort(vec2);
//	}
//	for (double d : arr) {
//		cout << d << " ";
//	}
//	cout << endl;
//}






void qSort(double* arr, int size)
{
	int first = 0;
	int last = size - 1;
	int elem = arr[size / 2];

	do {
		while (arr[first] < elem)
			first++;
		while (arr[last] > elem)
			last--;

		if (first <= last) {
			int tmp = arr[first];
			arr[first] = arr[last];
			arr[last] = tmp;
			first++;
			last--;
		}
	} while (first <= last);


	if (last > 0)
		qSort(arr, last + 1);
	if (first < size)
		qSort(&arr[first], size - first);
}

void printArray(double* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void main()
{
	double* arr = new double[5];
	arr[0] = 6;
	arr[1] = 4;
	arr[2] = 1;
	arr[3] = 9;
	arr[4] = 3;
	printArray(arr, 5);
	qSort(arr, 5);
	printArray(arr, 5);





	/*cout << " hello" <<endl;
	vector <double> vec = { 6,4,1,9,3 };
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
	cout << "qq";
	q_Sort(vec);
	cout << "rere";
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
	cout << "@@@@@@@@@@@@@@@@" << endl;*/
	//delete[]vec;
	system("pause>>void");
}