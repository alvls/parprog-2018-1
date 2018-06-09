#include <cstdio>
#include <cstring>
#include <string>
#include "omp.h"
#include <iostream>
#include <chrono>

#define PI 3.14159265358979323846

typedef struct {
	double value[3]{ 0,0,0 };
	double weight[3]{ 0,0,0 };
} Weights; //struct for filter algorithm

double* gaussian_blur_parallelMP(double* image, int h, int w, double r);

int border(int val, int min, int max, int r = 0) {
	if (val < min) return min + r; //when out of border - mirror pixels
	if (val > max) return max - r;
	return val;
}

double* read_binary_image_file(int&w, int&h, const std::string& dir = "image.in") {
	freopen(dir.c_str(), "rb", stdin);
	fread(&w, sizeof(w), 1, stdin);
	fread(&h, sizeof(h), 1, stdin);
	double *data = new double[h * w * 3];
	fread(data, sizeof(*data), h * w * 3, stdin);
	return data;
}

void save_image_to_binary(int&w, int&h, double *data, double& t, const std::string& dir = "image.out")
{
	freopen(dir.c_str(), "wb", stdout);
	fwrite(&w, sizeof(w), 1, stdout);
	fwrite(&h, sizeof(h), 1, stdout);
	fwrite(&t, sizeof(t), 1, stdout);
	fwrite(data, sizeof(*data), h * w * 3, stdout);
}

int main(int argc, const char** argv)
{
	int w, h; //image size
	double *data; //pixels by lines R,G,B,R,G,B,R...
	int threads_num = argc > 1 ? std::stoi(argv[1]) : 4; //count of threads
	int radius = argc > 2 ? std::stoi(argv[2]) : 1; //filter radius 1 by default (3x3)
	std::string input_file = argc > 3 ? std::string(argv[3]) : "image.in"; //file dir
	std::string output_file = argc > 4 ? std::string(argv[4]) : "image.out"; //file dir
	omp_set_num_threads(threads_num);

	data = read_binary_image_file(w, h, input_file);

	//future OpenMP version mb in another project
	double parallel_time = omp_get_wtime();
	double* blured = gaussian_blur_parallelMP(data, h, w, radius);
    parallel_time = omp_get_wtime() - parallel_time;
	printf("Parallel time: %lfs\n", parallel_time);
    save_image_to_binary(w, h, blured, parallel_time, output_file);

	delete[] blured;
	delete[] data;
	return 0;
}

double* gaussian_blur_parallelMP(double* image, int h, int w, double r) {	
	double* res = new double[h * w * 3];
#pragma omp parallel for schedule(guided) shared(image)
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			Weights weights;
			for (int iy = i - r; iy<i + r + 1; iy++) {
				for (int ix = j - r; ix < j + r + 1; ix++) {

					int x = border(ix, 0, w - 1,r);
					int y = border(iy, 0, h - 1,r);
					double dsq = (ix - j) * (ix - j) + (iy - i) * (iy - i);
					double wght = exp(-dsq / (2 * r * r)) / (PI * 2 * r * r);
					for (int c = 0; c < 3; c++) {
						weights.value[c] += image[w * y * 3 + x * 3 + c] * wght;
						weights.weight[c] += wght;
					}
				}
			}
			for (int c = 0; c < 3; c++) {
				res[w * i * 3 + j * 3 + c] = round(weights.value[c] / weights.weight[c]);
				weights.value[c] = 0.0;
				weights.weight[c] = 0.0;
			}
		}
	}
	return res;
}
