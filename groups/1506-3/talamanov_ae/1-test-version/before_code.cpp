#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "shellsort.hpp"

using Time = std::chrono::high_resolution_clock;
using ms   = std::chrono::milliseconds;
using fms  = std::chrono::duration<float, std::milli>;

int main(int argc, char* argv[]) {
  int sort_type     = atoi(argv[1]);
  int size_array    = atoi(argv[2]);
  int count_threads = atoi(argv[3]);

  std::uniform_int_distribution<int> distribution(-1000000, 1000000);
  std::mt19937 generator{std::random_device()()};
  std::vector<int> v1(size_array);

  std::generate(v1.begin(), v1.end(), [&distribution, &generator]{
        return distribution(generator);
      });

  std::vector<int> v2(v1);
  std::sort(v2.begin(), v2.end());

  std::chrono::time_point<Time> start;
  std::chrono::time_point<Time> end;

  switch (sort_type) {
    case 1:
      start = std::chrono::high_resolution_clock::now();
      ShellSort(v1.begin(), v1.end());
      end = std::chrono::high_resolution_clock::now();
      break;
    case 2:
      start = std::chrono::high_resolution_clock::now();
      // OmpShellSort(v1.begin(), v1.end(), count_threads);
      end = std::chrono::high_resolution_clock::now();
      break;
    case 3:
      start = std::chrono::high_resolution_clock::now();
      // TbbShellSort(v1.begin(), v1.end(), count_threads);
      end = std::chrono::high_resolution_clock::now();
      break;
    default:
      throw std::invalid_argument("Sort with this type doesn't exist");
  }

  if (v1 == v2) {
    std::cout << "Array is sorted " << std::endl;
  } else {
    std::cout << "Array isn't sorted " << std::endl;
  }

  fms elapsed_time = end - start;
  std::cout << "time = " << elapsed_time.count() << "ms" << std::endl;

  return 0;
}
