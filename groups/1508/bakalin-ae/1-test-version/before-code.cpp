#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include "point.h"
#include <omp.h>
#include <iostream>

void JarvisAlgorithm(Point* data, Point* result, int in_size, int &out_size);

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "JARVIS ALGORITHM PROGRAM\n" << "To use this program, please stick to the following pattern:\n" <<
			"solver [input] [output] [num of threads]" << std::endl;
		return 1;
	}

	int num_threads = 1;
	
	if (argc > 3)
		num_threads = atoi(argv[3]);
	
	int size, out_size;
	Point *in, *out;

	freopen(argv[1], "rb", stdin);

	fread(&size, sizeof(size), 1, stdin);

	in = new Point[size];
	out = new Point[size];

	fread(in, sizeof(*in), size, stdin);

	omp_set_num_threads(num_threads);

	double time = omp_get_wtime();
	JarvisAlgorithm(in, out, size, out_size);
	time = omp_get_wtime() - time;

	freopen(argv[2], "wb", stdout);
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&out_size, sizeof(out_size), 1, stdout);

	if (out_size > 0) {
		fwrite(out, sizeof(*out), out_size, stdout);
	}

	return 0;
}
