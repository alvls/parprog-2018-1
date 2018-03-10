#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include "point.h"

using namespace std;

int main() {
	int size;
	Point *data;
	ifstream file("../in.txt");

	file >> size;
	data = new Point[size];

	for (int i = 0; i < size; i++) {
		file >> data[i].x;
		file >> data[i].y;
	}

	freopen("../points.in", "wb", stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	fwrite(data, sizeof(*data), size, stdout);

	return 0;
}
