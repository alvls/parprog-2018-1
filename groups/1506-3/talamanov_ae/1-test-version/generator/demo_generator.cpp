#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include <stdexcept>
#include "generator.hpp"

using std::cerr;
using std::runtime_error;
using std::string;
using std::vector;
using std::ofstream;
using std::copy;
using std::ios;
using std::endl;
using std::ostream_iterator;

void writeArrayToFile(vector<int> array, const string& file_name);

int main(int argc, char* argv[]) {
  if (argc != 4) {
    cerr << "You should set :" << endl;
    cerr << "number test = [0, 5]" << endl;
    cerr << "array size " << endl;
    cerr << "output file path " << endl;

    throw runtime_error("invalid parameters");
  }

  auto type = static_cast<Generator::TestType>(atoi(argv[1]));
  int size_array = atoi(argv[2]);
  string out_file_path = string(argv[3]);

  Generator generator;
  auto array = generator.generate(type, size_array);

  writeArrayToFile(array, out_file_path);

  return 0;
}

void writeArrayToFile(vector<int> array, const string& file_path) {
  ofstream file(file_path, ios::binary);

  ostream_iterator<int> file_iterator(file, " ");
  copy(array.begin(), array.end(), file_iterator);

  file.close();
}
