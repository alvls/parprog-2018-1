#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include "point.h"
#include <omp.h>
#include <iostream>

void JarvisAlgorithm(Point* data, Point* result, int in_size, int &out_size);

int main(int argc, char* argv[]) {
	
	int num_threads = 1;
	
	if (argc > 1)
		num_threads = atoi(argv[1]);
	
	int size, out_size;
	Point *in, *out;

	freopen("../points.in", "rb", stdin);

	fread(&size, sizeof(size), 1, stdin);

	in = new Point[size];
	out = new Point[size];

	fread(in, sizeof(*in), size, stdin);

	omp_set_num_threads(num_threads);

	double time = omp_get_wtime();
	JarvisAlgorithm(in, out, size, out_size);
	time = omp_get_wtime() - time;

	freopen("../points.out", "wb", stdout);
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&out_size, sizeof(out_size), 1, stdout);
	fwrite(out, sizeof(*out), out_size, stdout);

	return 0;

	/*int size = 7;
	int out_size;
	
	if (argc > 1)
		size = atoi(argv[1]);

	Point* data = new Point[size];
	Point* result = new Point[size];
	
	data[0].x = 2; data[0].y = 2;
	data[1].x = 0; data[1].y = 3;
	data[2].x = 1; data[2].y = 1;
	data[3].x = 2; data[3].y = 1;
	data[4].x = 3; data[4].y = 0;
	data[5].x = 0; data[5].y = 0;
	data[6].x = 3; data[6].y = 3;
	
	JarvisAlgorithm(data, result, size, out_size);

	std::cout << out_size << std::endl;
	for (int i = 0; i < out_size; i++) {
		std::cout << "(" << result[i].x << ", " << result[i].y << ")" << std::endl;
	}*/

	return 0;
}