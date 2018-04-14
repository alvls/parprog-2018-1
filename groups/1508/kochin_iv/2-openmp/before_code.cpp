#include <cstdio>
#include <string>
#include <omp.h>
#include <iostream>

using namespace std;

double* Gauss(double* image, int width, int height, double Sigma = 3, int radius = 1);
double* read_binary_image_file(int&w, int&h, const std::string& dir = "bin.in");
void save_image_to_binary(int&w, int&h, double *data, const std::string& dir = "bin.out");
int main(int argc, char * argv[])
{
	string INPUT = "bin.in";
	string OUTPUT = "bin.out";
	uint8_t NUM_THREADS=1;
	if (argc > 1)
		INPUT = string(argv[1]);
	if (argc > 2)
		OUTPUT = string(argv[2]);
	if (argc > 3)
		NUM_THREADS = stoi(argv[3]);
	double * image, *result;
	int width, height;
	double time;

	image = read_binary_image_file(width, height, INPUT);
	omp_set_num_threads(NUM_THREADS);
	time = omp_get_wtime();
	result = Gauss(image, width, height);
	cout << "Time of calculating " << omp_get_wtime() - time << endl;
	save_image_to_binary(width, height, result, OUTPUT);

	delete[] result;
	delete[] image;

	return 0;
}