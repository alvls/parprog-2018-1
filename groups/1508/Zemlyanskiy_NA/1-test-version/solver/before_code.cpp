//9. Сортировка Шелла с четно-нечетным слиянием Бэтчера.
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <omp.h>
#include <string>
#include "sol.cpp"

using namespace std;

template <typename T>
void Shell_Sort(T *Arr, unsigned int length);

int main(int argc, char *argv[]) {
  if(argc != 3) {
    cout<<"Can't run the programm"<<endl;
    cout << "Please enter the arguments" << endl;
    cout << "Like this: ./before_code [in_file_name.bin] [out_file_name.bin]"<<endl;
    exit(-1);
  }

  int length = 0;

  string start_in_name = "tests/input/";
  string start_out_name = "tests/output/";
  string end_in_name = argv[1];
  string end_out_name = argv[2];

  string in_file_name = start_in_name + end_in_name;
  string out_file_name = start_out_name + end_out_name;

  FILE* in_file = fopen(in_file_name.c_str(), "rb");
  FILE* out_file = fopen(out_file_name.c_str(), "wb");

  fread(&length, sizeof(length), 1, in_file);

  int *Arr_Shell = new int[length];

  fread(Arr_Shell,sizeof(*Arr_Shell), length, in_file);

  Shell_Sort(Arr_Shell, length);

  fwrite(&length, sizeof(length), 1, out_file);
  fwrite(Arr_Shell,sizeof(*Arr_Shell),length,out_file);

  cout << "THE END" << endl;

  delete Arr_Shell;
  fclose(in_file);
  fclose(out_file);

  return 0;
}
