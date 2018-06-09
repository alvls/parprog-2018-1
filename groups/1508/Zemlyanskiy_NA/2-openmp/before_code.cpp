//9. Сортировка Шелла с четно-нечетным слиянием Бэтчера.
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <omp.h>
#include <string>
#include "omp.cpp"

using namespace std;

template <typename T>
void Shell_Sort(T *Arr, unsigned int length);

//Слияние Бэтчера
template <typename T>
void OddEvenMergeSort(vector<T> v1, vector<T> v2, T* out, int num_threads) {
  int i, j;
  int size1 = v1.size();
  int size2 = v2.size();

  if(num_threads % 2 == 0) {
    i = 0;
    j = 0;
  }
  else {
    i = 1;
    j = 1;
  }

  for(i; i < size1; i++) {
    for(j = 0; j < size2; j++) {
      out[i + j] = v1[i];
      out[i + j + 1] = v2[i];
    }
  }

  for(i; i < size1; i++) {
    out[size1 + i] = v1[i];
  }

  for(j; j < size2; j++) {
    out[size2 + i] = v2[j];
  }

  for(i; i < (size1 + size2 - 1); i++) {
    if(out[i] > out[i + 1]) {
      swap(out[i], out[i + 1]);
    }
  }
}

int main(int argc, char *argv[]) {
  if(argc != 4) {
    cout<<"Can't run the programm"<<endl;
    cout << "Please enter the arguments" << endl;
    cout << "Like this: ./before_code [in_file_name.bin] [out_file_name.bin] [number_of_threads]"<<endl;
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

  int num_threads = atoi(argv[3]);

  fread(&length, sizeof(length), 1, in_file);

  int *Arr_Shell = new int[length];
  vector<int> v1(length / num_threads);
  vector<int> v2(length / num_threads);
  fread(Arr_Shell,sizeof(*Arr_Shell), length, in_file);
  int pod_length = length / num_threads;

  double time = omp_get_wtime();
  omp_set_num_threads(num_threads);
  #pragma omp parallel
  {
    Shell_Sort(Arr_Shell, length, num_threads);
  }
  while(num_threads > 0) {
    for(int i = 0; i < pod_length; i++) {
      if(num_threads % 2 == 0) {
        v1[i] = Arr_Shell[i];
    }
    else {
      v2[i] = Arr_Shell[i];
    }
  }
    num_threads--;
}
  while(num_threads > 0) {
    OddEvenMergeSort(v1, v2, Arr_Shell, num_threads);
    num_threads--;
  }

  time = omp_get_wtime() - time;
  fwrite(&time, sizeof(time), 1, out_file);
  fwrite(&length, sizeof(length), 1, out_file);
  fwrite(Arr_Shell,sizeof(*Arr_Shell),length,out_file);

  cout << "THE END" << endl;

  delete Arr_Shell;
  fclose(in_file);
  fclose(out_file);
  return 0;
}
