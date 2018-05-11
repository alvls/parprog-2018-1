#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include "tbb\tick_count.h"
#include "tbb\tbb.h"

void Sobel(int* sourceImg, int* newImg, int width, int height, int* kernel);
void Typer(char* imgname, char* binaryname);
void Viewer(char* binaryname, char* imgname);

int main(int argc, char* argv[]) {

	Typer("spock.png", "test.in");

	freopen("test.in", "rb", stdin);
	freopen("test.out", "wb", stdout);

	int width = 0,
		height = 0,
		type = 0;

	fread(&width, sizeof(width), 1, stdin);
	fread(&height, sizeof(height), 1, stdin);
	fread(&type, sizeof(type), 1, stdin);

	int* sourceImg = new int[width * height];
	int* newImg = new int[width * height];

	fread(sourceImg, sizeof(*sourceImg), width * height, stdin);

	int kernel[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

	tbb::task_scheduler_init init;

	tbb::tick_count start = tbb::tick_count::now();
	Sobel(sourceImg, newImg, width, height, kernel);
	tbb::tick_count finish = tbb::tick_count::now();
	double time = (double)(finish - start).seconds();

	fwrite(&width, sizeof(width), 1, stdout);
	fwrite(&height, sizeof(height), 1, stdout);
	fwrite(&type, sizeof(type), 1, stdout);
	fwrite(newImg, sizeof(*newImg), width * height, stdout);
	fwrite(&time, sizeof(time), 1, stdout);

	delete[] sourceImg;
	delete[] newImg;

	fclose(stdin);
	fclose(stdout);

	Viewer("test.out", "spock_r.png");

	return 0;
}