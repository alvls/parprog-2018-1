#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

double* Gauss(double* image, int width, int height, double Sigma=1,int radius=1)
{	
	//We used 1-dimentional array for three chanels(R,G,B)
	double* result = (double*)malloc(sizeof(double)*width*height * 3);

	//initialize kernel
	double kernel[3][3];
	double norm = 0;
	//caclulate kernel
	for (int i =-radius;i<=radius;i++)
		for (int j = -radius; j <=radius; j++) {
			kernel[i+radius][j+radius] = exp(-(i*i+j*j)/(Sigma*Sigma));
			norm += kernel[i + radius][j + radius];
		}
	//normalize kernel
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			kernel[i][j] /= norm;
	int x, y;
	//delete garbage
	for (int i = 0; i < width*height * 3; i++) {
		result[i] = 0;
	}

	for (x = radius; x < width - radius; x++)
		for (y = radius; y < height - radius; y++)
		{
			for (int i = -radius; i <= radius; i++)
				for (int j = -radius; j <= radius; j++) {
					//for RED channel
					result[x*height + y] += image[(x + i)*height + y + j] * kernel[radius - i][radius - j];
					//for GREEN channel
					result[(x*height + y)*2] += image[((x + i)*height + y + j)*2] * kernel[radius - i][radius - j];
					//for BLUE channel
					result[(x*height + y)*3] += image[((x + i)*height + y + j) * 3] * kernel[radius - i][radius - j];
				}
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
