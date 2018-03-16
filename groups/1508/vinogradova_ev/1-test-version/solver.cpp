//Выделение ребер на изображении с использованием оператора Собеля.

#include <iostream>

int Clamp(int value, int min, int max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

void Sobel(int* sourceImg, int* newImg, int width, int height)
{
	int radius = 1;
	int kernel[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int resultColorX = 0;
			int resultColorY = 0;
			for (int l = -radius; l <= radius; l++) {
				for (int k = -radius; k <= radius; k++) {
					int idX = Clamp(j + k, 0, width - 1);
					int idY = Clamp(i + l, 0, height - 1);
					int neighbColor = sourceImg[idY*width + idX];
					resultColorX += neighbColor * kernel[(l + radius) * 3 + (k + radius)];
					resultColorY += neighbColor * kernel[(k + radius) * 3 + (l + radius)];
				}
			}
			newImg[i * width + j] = Clamp((int)sqrt(resultColorX*resultColorX + resultColorY*resultColorY), 0, 255);
		}
	}
}