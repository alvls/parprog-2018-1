#include <string>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <chrono>
#include "logger.h"
#include "shellsort.h"

using namespace std;

vector<int> loadArrayFromFile(string file_path);

int main(int argc, char* argv[]) {
  if(argc != 3){
    cerr << "You should set : " << endl;
    cerr << "path to binary file with test array" << endl;
    cerr << "path to log file " << endl;
    throw runtime_error("invalid parameters");
  }

  string in_array_path = string(argv[1]);
  string log_file_parh = string(argv[2]);

  Logger checker_result(log_file_parh);

  auto array = loadArrayFromFile(in_array_path);

  auto start = chrono::high_resolution_clock::now();
  ShellSort(array.begin(), array.end());
  auto finish = chrono::high_resolution_clock::now();

  bool is_sorted = std::is_sorted(array.begin(), array.end());
  int  elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();

  if(is_sorted){
    checker_result.writeMessage("AC. Array is sorted");
    checker_result.writeVerdict(verdict::AC);
  }else{
    checker_result.writeMessage("WA. Array is't sortded");
    checker_result.writeVerdict(verdict::WA);
  }

  checker_result.writeTime(elapsed_ns);
  checker_result.writeMemory(array.size() * sizeof(int));

  return 0;
}

vector<int> loadArrayFromFile(string file_path) {
  ifstream file(file_path);
  vector<int> array;

  if(!file){
    throw runtime_error("failed open file");
  }

  istream_iterator<int> begin_file(file);
  istream_iterator<int> end_file;

  copy(begin_file, end_file, back_inserter(array));

  file.close();

  return array;
}
