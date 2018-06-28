#include <fstream>
#include <iostream>
#include <omp.h>

unsigned char *allocateSolution(unsigned char *img, int width, int height);

int main(int argc, char *argv[])
{
	int width, height; // Размеры изображения
	std::ifstream ifs(argv[1], std::ios::binary);
	ifs.read((char *)&width, sizeof(width));
	ifs.read((char *)&height, sizeof(height));

	int imageLength = width * height * 3;
	unsigned char *img = new unsigned char[imageLength];
	ifs.read((char *)img, imageLength);
	ifs.close();

	// Решение задачи
	double time = omp_get_wtime();
	unsigned char *res = allocateSolution(img, width, height);
	time = omp_get_wtime() - time;

	std::ofstream ofs(argv[2], std::ios::binary);
	ofs.write((char *)&width, sizeof(width));
	ofs.write((char *)&height, sizeof(height));
	ofs.write((char *)res, imageLength);
	ofs.write((char *)&time, sizeof(time));
	ofs.close();

	delete[] img;
	delete[] res;

	std::cout << "Решение записано в " << argv[2] << '.' << std::endl;

	return 0;
}
