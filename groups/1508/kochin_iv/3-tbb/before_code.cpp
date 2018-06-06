#include <cstdio>
#include <string>
#include <iostream>
#include <tbb/tick_count.h>
#include <tbb/task_scheduler_init.h>
using namespace std;

double* Gauss(double* image, int width, int height, double Sigma = 3, int radius = 1);
double* read_binary_image_file(int&w, int&h, const std::string& dir = "bin.in");
void save_image_to_binary(int&w, int&h, double *data, const std::string& dir = "bin.out");
int main(int argc, char * argv[])
{
	string INPUT = "bin.in";
	string OUTPUT = "bin.out";
	uint8_t NUM_THREADS = 1;
	if (argc > 1)
		INPUT = string(argv[1]);
	if (argc > 2)
		OUTPUT = string(argv[2]);
	if (argc > 3)
		NUM_THREADS = stoi(argv[3]);
	double * image, *result;
	int width, height;
	double time;
	tbb::task_scheduler_init init(NUM_THREADS);

	

	image = read_binary_image_file(width, height, INPUT);
	auto parallel_time = tbb::tick_count::now();
	result = Gauss(image, width, height);
	time = (tbb::tick_count::now() - parallel_time).seconds();
	save_image_to_binary(width, height, result, OUTPUT);
	//cout<<"Time of calculating %f"<<endl;
	delete[] result;
	delete[] image;
	time = 0;
	return 0;
}