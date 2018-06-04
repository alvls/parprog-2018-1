#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <opencv2\opencv.hpp>

using namespace cv;

void Typer(char* imgname, char* binaryname) {

	Mat img = imread(imgname);

	freopen(binaryname, "wb", stdout);

	int width = img.cols,
		height = img.rows,
		type = img.type();

	fwrite(&width, sizeof(width), 1, stdout);
	fwrite(&height, sizeof(height), 1, stdout);
	fwrite(&type, sizeof(type), 1, stdout);

	int* tmp_row = new int[width * height];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			tmp_row[i * width + j] = 0.36 * img.at<Vec3b>(i, j)[2] + 0.53 * img.at<Vec3b>(i, j)[1] + 0.11 * img.at<Vec3b>(i, j)[0];
	fwrite(tmp_row, sizeof(*tmp_row), width * height, stdout);
	fclose(stdout);

	delete[] tmp_row;
}
