#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include "point.h"

using namespace std;

int main(int argc, char *argv[]) {
	int size;
	double time;
	Point *data;

	if (argc != 3) {
		return 0;
	}

	ofstream file(argv[2]);

	freopen(argv[1], "rb", stdin);
	fread(&time, sizeof(time), 1, stdin);
	fread(&size, sizeof(size), 1, stdin);

	data = new Point[size];

	fread(data, sizeof(*data), size, stdin);

	file << time << " ";
	file << size << " ";

	for (int i = 0; i < size; i++) {
		file << data[i].x << " " << data[i].y << " ";
	}

	return 0;
}