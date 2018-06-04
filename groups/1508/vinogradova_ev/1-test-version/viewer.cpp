#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <opencv2\opencv.hpp>

using namespace cv;

void Viewer(char* binaryname, char* imgname) {

	int width = 0,
		height = 0,
		type = 0;

	freopen(binaryname, "rb", stdin);
	fread(&width, sizeof(width), 1, stdin);
	fread(&height, sizeof(height), 1, stdin);
	fread(&type, sizeof(type), 1, stdin);

	Mat img(height, width, type);
	int* tmp_img = new int[width * height];

	fread(tmp_img, sizeof(*tmp_img), width * height, stdin);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			img.at<Vec3b>(i, j)[0] = tmp_img[i * width + j];
			img.at<Vec3b>(i, j)[1] = tmp_img[i * width + j];
			img.at<Vec3b>(i, j)[2] = tmp_img[i * width + j];
		}
	}
	imwrite(imgname, img);
	fclose(stdin);
	delete[] tmp_img;
}
