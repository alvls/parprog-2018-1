#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <ctime>
#include <chrono>

using namespace std;

int n_tests[] = { 0, 1, 12, 13, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600,
1700, 1800, 1900, 2000, 1111, 2222, 3333, 4444, 5555, 6666, 7777, 8888, 9999, 11111, 100000, 1000000 };

int main(int argc, char * argv[]) {
  if(argc < 1) {
    cout<<"Can't run the programm"<<endl;
    cout << "Please enter the arguments" << endl;
    cout << "Like this: ./generator [number_of_test/file_name]"<<endl;
    exit(-1);
  }

  string start_name = "tests/input/";
  string end_name = argv[1];

  string file_name = start_name + end_name;
  FILE* bin_file = fopen(file_name.c_str(), "wb");

  default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());


  uniform_int_distribution <int> distribution(-1000000, 1000000);

  int length = n_tests[atoi(argv[1])];

  fwrite(&length, sizeof (length), 1, bin_file);

  int* Arr = new int[length];

  for(int i = 0; i < length; i++) {
    if(atoi(argv[1]) >= 34)
      Arr[i] = rand() % 1000000;
    else
      Arr[i] = distribution(generator);
  }
  fwrite(Arr, sizeof (*Arr), length, bin_file);

  delete Arr;
  fclose(bin_file);

  return 0;
}
