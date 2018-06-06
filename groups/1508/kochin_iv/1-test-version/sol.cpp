#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

double** createGaussianKernel(int radius, double sigma)
{
	// определяем размер ядра
	int size = 2 * radius + 1;
	// создаем ядро фильтра
	double ** kernel = new double*[size];
	for (int i = 0; i < size; i++)
		kernel[i] = new double[size];
	// коэфицент нормировки ядра
	double norm = 0;
	// рассчитываем ядро линейного фильтра
	for (int i = -radius; i <= radius; i++)
		for (int j = -radius; j <= radius; j++)
		{
			kernel[i + radius][j + radius] = (double)(exp(-(i * i + j * j) / (sigma * sigma)));
			norm += kernel[i + radius][j + radius];
		}
	//нормируем ядро
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			kernel[i][j] /= norm;
	return kernel;
}

double* Gauss(double* image, int width, int height, double Sigma = 3, int radius = 1)
{
	//We used 1-dimentional array for three chanels(R,G,B)
	double* result = (double*)malloc(sizeof(double)*width*height * 3);
	radius = 2;
	int x, y;
	//delete garbage
	for (int i = 0; i < width * height * 3; i++) {
		result[i] = 0;
	}

	double** kernel = createGaussianKernel(radius, Sigma);
	/*(for (y = 0; y < height; y++)
		for (x = 0; x < radius; x++) {
			//PAINTING LEFT BLACK LINE
			//for RED channel
			result[(y*width + x) * 3] += image[(y*width + x) * 3];
			//for GREEN channel
			result[(y*width + x) * 3 + 1] += image[(y*width + x) * 3 + 1];
			//for BLUE channel
			result[(y*width + x) * 3 + 2] += image[(y*width + x) * 3 + 2];
			//PAINTING RIGHT BLACK LINE
			//for RED channel
			result[(y*width + width-1-x) * 3] += image[(y*width + width - 1 - x) * 3];
			//for GREEN channel
			result[(y*width + width-1 - x) * 3 + 1] += image[(y*width + width - 1 - x) * 3 + 1];
			//for BLUE channel
			result[(y*width + width - 1 - x) * 3 + 2] += image[(y*width + width - 1 - x) * 3 + 2];
		}
	for (x = 0; x < width; x++)
		for (y = 0; y < radius; y++) {
			//PAINTING LEFT BLACK LINE
			//for RED channel
			result[(y*width + x) * 3] += image[(y*width + x) * 3];
			//for GREEN channel
			result[(y*width + x) * 3 + 1] += image[(y*width + x) * 3 + 1];
			//for BLUE channel
			result[(y*width + x) * 3 + 2] += image[(y*width + x) * 3 + 2];
			//PAINTING RIGHT BLACK LINE
			//for RED channel
			result[((height-1-y)*width + x) * 3] += image[((height-1 - y)*width +x) * 3];
			//for GREEN channel
			result[((height-1 - y)*width + x) * 3 + 1] += image[((height-1 - y)*width + x) * 3 + 1];
			//for BLUE channel
			result[((height-1 - y)*width + x) * 3 + 2] += image[((height-1 - y)*width + x) * 3 + 2];
		}*/
	for (int i = 0; i < width*height * 3; i++) {
		result[i] = image[i];
	}
	for (y = radius; y < height - radius; y++)
		for (x = radius; x < width - radius; x++){
			//for RED channel
			result[(y*width + x) * 3] =0;
			//for GREEN channel
			result[(y*width + x) * 3 + 1] =0;
			//for BLUE channel
			result[(y*width + x) * 3 + 2] =0;
		}
			

	for (y = radius; y < height - radius; y++)
		for (x = radius; x < width - radius; x++)
		{
			for (int i = -radius; i <= radius; i++)
				for (int j = -radius; j <= radius; j++) {
					//for RED channel
					result[(y*width + x) * 3] += image[((y + i)*width + x + j) * 3] * kernel[radius + i][radius + j];
					//for GREEN channel
					result[(y*width + x) * 3 + 1] += image[((y + i)*width + x + j) * 3 + 1] * kernel[radius + i][radius + j];
					//for BLUE channel
					result[(y*width + x) * 3 + 2] += image[((y + i)*width + x + j) * 3 + 2] * kernel[radius + i][radius + j];
				}
		}
	for (int i = 0; i < width * height * 3; i++) {
		result[i] = (int)result[i];
	}
	return result;
}

double* read_binary_image_file(int&w, int&h, const std::string& dir = "bin.in") {
	FILE *file;
	freopen_s(&file, dir.c_str(), "rb", stdin);
	fread(&w, sizeof(w), 1, stdin);
	fread(&h, sizeof(h), 1, stdin);
	double *data = new double[h * w * 3];
	fread(data, sizeof(*data), h * w * 3, stdin);
	return data;
}

void save_image_to_binary(int&w, int&h, double *data, const std::string& dir = "bin.out")
{
	FILE *file;
	freopen_s(&file, dir.c_str(), "wb", stdout);
	fwrite(&w, sizeof(w), 1, stdout);
	fwrite(&h, sizeof(h), 1, stdout);
	fwrite(data, sizeof(*data), h * w * 3, stdout);
}

