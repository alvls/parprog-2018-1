#include <cstdio>

#include "stdafx.h"
#include <random>
#include <tbb\tbb.h>
#include <iostream>

struct Cell {
	bool bit = false;//bit map
	int tag = -1;//mark num
};

Cell** tbb_alg(int w, int h, int *arr);


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

	tbb::tick_count t0 = tbb::tick_count::now();
	out = tbb_alg(size, size, in);
	tbb::tick_count t1 = tbb::tick_count::now();
	std::cout << (t1-t0).seconds() << " - time" << std::endl;

	auto time = (t1 - t0).seconds();
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);

	for (int i = 0; i < size; i++) {
		for (int k = 0; k < size; k++) {
			in[i*size + k] = out[i][k].tag;
		}
	}

	fwrite(in, sizeof(*in), size, stdout);
	getchar();

	return 0;
}
