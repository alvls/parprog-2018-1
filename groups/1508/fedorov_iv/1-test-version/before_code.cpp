#include <cstdio>

#include "stdafx.h"
#include <random>
#include <omp.h>
#include <iostream>

struct Cell {
	bool bit = false;//bit map
	int tag = -1;//mark num
};

Cell** serial_alg(int w, int h, int *arr);

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "ALGORITHM PROGRAM\nTo use this program, please stick to the following pattern:\n" <<
			"solver [input] [output]" << std::endl;
		return 1;
	}

	int num_threads = 1;

	if (argc > 1)
		num_threads = atoi(argv[1]);

	int size;
	int *in;
	Cell **out;

	freopen(argv[1], "rb", stdin);

	fread(&size, sizeof(size), 1, stdin);

	in = new int[size*size];

	fread(in, sizeof(*in), size, stdin);

	omp_set_num_threads(num_threads);

	double time = omp_get_wtime();
	out = serial_alg(size, size, in);
	time = omp_get_wtime() - time;

	freopen(argv[2], "wb", stdout);
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < size; k++) {
			in[i*size + k] = out[i][k].tag;
		}
	}

	if (size > 0) {
		fwrite(in, sizeof(*in), size, stdout);
	}

	return 0;
}
