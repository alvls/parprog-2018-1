#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include "tbb/tbb.h"
#include "tbb/tick_count.h"

#define PI 3.14159265358979323846
using data_vec = std::vector<double>;
typedef struct {
	double value[3];
	double weight[3];
} Weights; //struct for filter algorithm

void gaussian_blur_parallelTBB(const data_vec& image, data_vec& result, int h, int w, double r);

int border(int val, int min, int max, int r = 0) {
	if (val < min) return min + r; //when out of border - mirror pixels
	if (val > max) return max - r;
	return val;
}

data_vec read_binary_image_file(int&w, int&h, const std::string& dir = "image.in") {
	freopen(dir.c_str(), "rb", stdin);
	fread(&w, sizeof(w), 1, stdin);
	fread(&h, sizeof(h), 1, stdin);
    data_vec data(h * w * 3, 0.0);
	fread(reinterpret_cast<void*>(&data[0]), sizeof(data[0]), h * w * 3, stdin);
	return data;
}

void save_image_to_binary(int&w, int&h, data_vec& data, double& t, const std::string& dir = "image.out")
{
	freopen(dir.c_str(), "wb", stdout);
	fwrite(&w, sizeof(w), 1, stdout);
	fwrite(&h, sizeof(h), 1, stdout);
	fwrite(&t, sizeof(t), 1, stdout);
	fwrite(reinterpret_cast<void*>(&data[0]), sizeof(data[0]), h * w * 3, stdout);
}

int main(int argc, const char** argv)
{
	int w, h; //image size
    data_vec data; //pixels by lines R,G,B,R,G,B,R...
	int threads_num = argc > 1 ? std::stoi(argv[1]) : 4; //count of threads
	int radius = argc > 2 ? std::stoi(argv[2]) : 1; //filter radius 1 by default (3x3)
	std::string input_file = argc > 3 ? std::string(argv[3]) : "image.in"; //file dir
	std::string output_file = argc > 4 ? std::string(argv[4]) : "image.out"; //file dir
    tbb::task_scheduler_init init(threads_num);

	data = read_binary_image_file(w, h, input_file);
    data_vec blured(h * w * 3, 0.0);

	auto parallel_time = tbb::tick_count::now();
    gaussian_blur_parallelTBB(data, blured, h, w, radius);
    double p_time = (tbb::tick_count::now() - parallel_time).seconds();
	//printf("Parallel time: %lfs\n", p_time);
    save_image_to_binary(w, h, blured, p_time, output_file);

	return 0;
}

void gaussian_blur_parallelTBB(const data_vec& image, data_vec& result, int h, int w, double r) {
    tbb::parallel_for(tbb::blocked_range<int>(0, h), [&image, &result, &h, &w, &r](const tbb::blocked_range<int>& heigth) {
        for (int i = heigth.begin(); i != heigth.end(); ++i) {
            for (int j = 0; j < w; j++) {
                Weights weights = {};
                for (int iy = i - r; iy < i + r + 1; iy++) {
                    for (int ix = j - r; ix < j + r + 1; ix++) {

                        int x = border(ix, 0, w - 1, r);
                        int y = border(iy, 0, h - 1, r);
                        double dsq = (ix - j) * (ix - j) + (iy - i) * (iy - i);
                        double wght = exp(-dsq / (2 * r * r)) / (PI * 2 * r * r);
                        for (int c = 0; c < 3; c++) {
                            weights.value[c] += image[w * y * 3 + x * 3 + c] * wght;
                            weights.weight[c] += wght;
                        }
                    }
                }
                for (int c = 0; c < 3; c++) {
                    result[w * i * 3 + j * 3 + c] = round(weights.value[c] / weights.weight[c]);
                    weights.value[c] = 0.0;
                    weights.weight[c] = 0.0;
                }
            }
        }
    });
}
