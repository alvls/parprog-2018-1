#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void Sobel(int* sourceImg, int* newImg, int width, int height);
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

	if (argc > 1)
		omp_set_num_threads(atoi(argv[1]));

	double time = omp_get_wtime();
	Sobel(sourceImg, newImg, width, height);
	time = omp_get_wtime() - time;

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
