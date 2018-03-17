#include <cstdio>
#include <string>

using namespace std;
double* Gauss(double* image, int width, int height, double Sigma=1,int radius=1);
double* read_binary_image_file(int&w, int&h, const std::string& dir = "bin.in");
void save_image_to_binary(int&w, int&h, double *data, const std::string& dir = "bin.out");
int main(int argc, char * argv[])
{
	string INPUT = "bin.in";
	string OUTPUT = "bin.out";
	if (argc > 1)
		INPUT = string(argv[1]);
	if (argc > 2)
		OUTPUT = string(argv[2]);
	double * image, * result;
	int width, height;

	image = read_binary_image_file(width, height,INPUT);

	result = Gauss(image, width, height, 1);

	save_image_to_binary(width, height, result, OUTPUT);

	delete[] result;
	delete[] image;

	return 0;
}