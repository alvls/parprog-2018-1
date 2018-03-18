#include <string>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <chrono>
#include "logger.hpp"
#include "shellsort.hpp"

using std::vector;
using std::cerr;
using std::endl;
using std::runtime_error;
using std::string;
using std::ifstream;
using std::istream_iterator;
using std::copy;

vector<int> loadArrayFromFile(const string& file_path);

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "You should set : " << endl;
    cerr << "path to binary file with test array" << endl;
    cerr << "path to log file " << endl;
    throw runtime_error("invalid parameters");
  }

  const string& in_array_path = argv[1];
  const string& log_file_parh = argv[2];

  Logger checker_result(log_file_parh);

  auto array = loadArrayFromFile(in_array_path);

  auto start = std::chrono::high_resolution_clock::now();
  ShellSort(array.begin(), array.end());
  auto finish = std::chrono::high_resolution_clock::now();

  bool is_sorted = std::is_sorted(array.begin(), array.end());
  int elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();

  if (is_sorted) {
    checker_result.writeMessage("AC. Array is sorted");
    checker_result.writeVerdict(verdict::AC);
  } else {
    checker_result.writeMessage("WA. Array is't sortded");
    checker_result.writeVerdict(verdict::WA);
  }

  checker_result.writeTime(elapsed_ns);
  checker_result.writeMemory(array.size() * sizeof(int));

  return 0;
}

vector<int> loadArrayFromFile(const string& file_path) {
  ifstream file(file_path);
  vector<int> array;

  if (!file) {
    throw runtime_error("failed open file");
  }

  istream_iterator<int> begin_file(file);
  istream_iterator<int> end_file;

  copy(begin_file, end_file, back_inserter(array));

  file.close();

  return array;
}
