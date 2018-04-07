#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "tbb_shellsort.hpp"

using Time = std::chrono::high_resolution_clock;
using ms   = std::chrono::milliseconds;
using fms  = std::chrono::duration<float, std::milli>;

int main(int argc, char* argv[]) {
  int size_array    = atoi(argv[1]);
  int count_threads = atoi(argv[2]);

  std::uniform_int_distribution<int> distribution(-1000000, 1000000);
  std::mt19937 generator{std::random_device()()};
  std::vector<int> v1(size_array);

  std::generate(v1.begin(), v1.end(), [&distribution, &generator]{
        return distribution(generator);
      });

  std::vector<int> v2(v1);
  std::sort(v2.begin(), v2.end());

  std::cout << std::endl;
  std::chrono::time_point<Time> start = Time::now();
  TbbShellSort(v1.begin(), v1.end(), count_threads);
  std::chrono::time_point<Time> end = Time::now();

  if (v1 == v2) {
    std::cout << "Array is sorted " << std::endl;
  } else {
    std::cout << "Array isn't sorted " << std::endl;
  }

  fms elapsed_time = end - start;
  std::cout << "time = " << elapsed_time.count() << "ms" << std::endl;

  return 0;
}
