#include <cmath>

float **allocateGaussianKernel(int radius, float sigma)
{
	int size = 2 * radius + 1; // Размер ядра
	float norm = 0; // Коэффициент нормировки ядра
	float **kernel = new float *[size]; // Ядро фильтра
	for (int i = 0; i < size; i++)
		kernel[i] = new float[size];

	// Расчитываем ядро линейного фильтра
	for (int i = -radius; i <= radius; i++)
		for (int j = -radius; j <= radius; j++)
		{
			kernel[i + radius][j + radius] = (float)(std::expf(-(i * i + j * j) / (sigma * sigma)));
			norm += kernel[i + radius][j + radius];
		}

	// Нормируем ядро
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			kernel[i][j] /= norm;

	return kernel;
}

template< class T >
T clamp(T value, T min, T max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

struct Colour
{
	unsigned char R;
	unsigned char G;
	unsigned char B;

	Colour(unsigned char _R = 0, unsigned char _G = 0, unsigned char _B = 0)
	{
		R = _R;
		G = _G;
		B = _B;
	}
};

Colour calculateNewPixelColour(unsigned char *sourceImage, int width, int height, int x, int y, float **kernel, int radius)
{
	float resultR = 0;
	float resultG = 0;
	float resultB = 0;

	for (int l = -radius; l <= radius; l++)
		for (int k = -radius; k <= radius; k++)
		{
			int idX = clamp(x + k, 0, width - 1) * 3;
			int idY = clamp(y + l, 0, height - 1) * 3;

			Colour neighbourColour;
			neighbourColour.R = sourceImage[idX + width * idY];
			neighbourColour.G = sourceImage[idX + width * idY + 1];
			neighbourColour.B = sourceImage[idX + width * idY + 2];

			resultR += neighbourColour.R * kernel[k + radius][l + radius];
			resultG += neighbourColour.G * kernel[k + radius][l + radius];
			resultB += neighbourColour.B * kernel[k + radius][l + radius];
		}

	return Colour(
		(clamp(int(resultR), 0, 255)),
		(clamp(int(resultG), 0, 255)),
		(clamp(int(resultB), 0, 255)));
}

unsigned char *allocateSolution(unsigned char *img, int width, int height)
{
	const int radius = 1;
	float **kernel = allocateGaussianKernel(radius, 2);
	unsigned char *res = new unsigned char[width * height * 3];

    #pragma omp parallel for shared(width, height, img, res, kernel, radius)
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
		{
			Colour newColour = calculateNewPixelColour(img, width, height, x, y, kernel, radius);
			int displacement = (x + width * y) * 3;
			res[displacement] = newColour.R;
			res[displacement + 1] = newColour.G;
			res[displacement + 2] = newColour.B;
		}

	for (int i = 0; i < 3; i++)
		delete[] kernel[i];
	delete[] kernel;
	return res;
}
