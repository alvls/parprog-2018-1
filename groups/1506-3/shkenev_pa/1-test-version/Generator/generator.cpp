#include <fstream>
#include <cstdlib>
#include <ctime>

// generator выходной_файл ширина высота
int main(int argc, char *argv[])
{
	int width = atoi(argv[2]); // ширина изображения
	int height = atoi(argv[3]); // высота изображения

	int imageLength = width * height * 3;
	unsigned char *image = new unsigned char[imageLength];

    srand((int)time(NULL));
    unsigned char colourR = rand();
    unsigned char colourG = rand();
    unsigned char colourB = rand();
	for (int j = 0; j < imageLength; j += width * 3)
	{
        for (int i = 0; i < width; i++)
        {
            image[j + i * 3] = colourR;
            image[j + i * 3 + 1] = colourG;
            image[j + i * 3 + 2] = colourB;
        }

        colourR += rand() % 7 - 3;
        colourG += rand() % 7 - 3;
        colourB += rand() % 7 - 3;
    }

    for (int i = 0; i < imageLength; i += rand() % 50)
        image[i] = rand();

	std::ofstream ofs(argv[1], std::ios::binary);
	ofs.write((char *)&width, sizeof(width));
	ofs.write((char *)&height, sizeof(height));
	ofs.write((char *)image, imageLength);
	ofs.close();
	delete[] image;

	return 0;
}
