#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <cstdlib>

void Typer(char* imgname, char* binaryname);
void Sobel(int* sourceImg, int* newImg, int width, int height);

void generate_rectangle(int size, int rectsize, int* arr) {
	int border = (size - rectsize) / 2;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			if (i >= border && i < size - border && j >= border && j < size - border)
				arr[i * size + j] = 0;
			else
				arr[i * size + j] = 255;
		}
}

void generate_line(int size, int linesize, int* arr) {
	int border = (size - linesize) / 2;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			if (j >= border && j < size - border)
				arr[i * size + j] = 0;
			else
				arr[i * size + j] = 255;
		}
}

void generate_grad(int size, int gradsize, int* arr) {
	int border = (size - gradsize) / 2;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			if (j >= border && j < size - border)
				arr[i * size + j] = (j - border) * 255 / (gradsize - 1);
			else
				arr[i * size + j] = 255;
		}
}

void WriteBinary(int width, int height, int type, int* matr, char* filename)
{
	freopen(filename, "wb", stdout);
	fwrite(&width, sizeof(width), 1, stdout);
	fwrite(&height, sizeof(height), 1, stdout);
	fwrite(&type, sizeof(type), 1, stdout);
	fwrite(matr, sizeof(*matr), width * height, stdout);
	fclose(stdout);
}

enum generate {NO, RECT, LINE, GRAD};

int main(int argc, char * argv[]) {
	
	char* help = "Possible parameters:\n<binary file name> <img file name> or\n<binary file name> -<type of img> <size of img> <size of element> [<ans file name>]\nwhere type of img: rect, line, grad";
	int img_size = 1000, elt_size = 600, type = 16;
	char* binaryfile = "img.in";
	char* imgfile = "spock.png";
	generate flag = RECT;
	if (argc > 1) {
		if (!strcmp(argv[1], "help")) {
			printf("%s", help);
			return 0;
		}
		binaryfile = argv[1];
	}
	if (argc > 2) {
		char* buf = argv[2];
		if (buf[0] != '-') {
			flag = NO;
			imgfile = buf;
		}
		else if (!strcmp(buf, "-rect"))
			flag = RECT;
		else if (!strcmp(buf, "-line"))
			flag = LINE;
		else if (!strcmp(buf, "-grad"))
			flag = GRAD;
		else {
			printf("%s", help);
			return 0;
		}
	}
	if (argc > 3)
		img_size = atoi(argv[3]);
	if (argc > 4)
		elt_size = atoi(argv[4]);

	int* arr = new int[img_size * img_size];

	switch (flag)
	{
	case NO:
		Typer(imgfile, binaryfile);
		break;
	case RECT:
		generate_rectangle(img_size, elt_size, arr);
		WriteBinary(img_size, img_size, type, arr, binaryfile);
		break;
	case LINE:
		generate_line(img_size, elt_size, arr);
		WriteBinary(img_size, img_size, type, arr, binaryfile);
		break;
	case GRAD:
		generate_grad(img_size, elt_size, arr);
		WriteBinary(img_size, img_size, type, arr, binaryfile);
		break;
	}

	if (argc > 5)
	{
		int* new_arr = new int[img_size * img_size];
		Sobel(arr, new_arr, img_size, img_size);
		WriteBinary(img_size, img_size, type, new_arr, argv[5]);
	}

	delete[] arr;

	return 0;
}
