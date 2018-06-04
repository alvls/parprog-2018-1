//Выделение ребер на изображении с использованием оператора Собеля.

#include <iostream>
#include <omp.h>
#include "tbb\tbb.h"
#define RAD 1

int Clamp(int value, int min, int max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

void Sobel(int* sourceImg, int* newImg, int width, int height, int* kernel)
{
	tbb::parallel_for(tbb::blocked_range<int>(0, height), [&sourceImg, &newImg, &width, &height, &kernel](const tbb::blocked_range<int>& h) {
		for (int i = h.begin(); i != h.end(); ++i) {
			for (int j = 0; j < width; j++) {
				int resultColorX = 0;
				int resultColorY = 0;
				for (int l = -RAD; l <= RAD; l++) {
					for (int k = -RAD; k <= RAD; k++) {
						int idX = Clamp(j + k, 0, width - 1);
						int idY = Clamp(i + l, 0, height - 1);
						int neighbColor = sourceImg[idY*width + idX];
						resultColorX += neighbColor * kernel[(l + RAD) * 3 + (k + RAD)];
						resultColorY += neighbColor * kernel[(k + RAD) * 3 + (l + RAD)];
					}
				}
				newImg[i * width + j] = Clamp((int)sqrt(resultColorX*resultColorX + resultColorY*resultColorY), 0, 255);
			}
		}
	});
}