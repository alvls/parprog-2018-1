#include <iostream>
#include <string>
#include <chrono>
#include <stdexcept>
#include "linearcorection.h"
//#include "omp_linearcorection.h"

using namespace std;
using namespace cv;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

int main(int argc, char const *argv[]) {
  string filepath = argv[1];
  Mat input_image = imread(filepath);
  int num_threads = atoi(argv[2]);
  Mat output_image(input_image.size(), CV_8UC1);
  std::chrono::time_point<Time> start, end;
  switch (atoi(argv[3])) {
    case 1:
      start = Time::now();
      linearCorection(input_image, output_image);
      end = Time::now();
      break;
    case 2:
      start = Time::now();
    //  ompLinearcorection(input_image, output_image, num_threads);
      end = Time::now();
      break;
    case 3:
      start = Time::now();
    //  tbbLinearcorection(input_image, output_image, num_threads);
      end = Time::now();
      break;
    default:
      throw std::invalid_argument("Enter 1, 2 or 3");
  }
  fsec sec = end-start;
  ms elapsed_mseconds = std::chrono::duration_cast<ms>(sec);
  cout << "time = " << elapsed_mseconds.count() << " ms" << endl;
  return 0;
}
