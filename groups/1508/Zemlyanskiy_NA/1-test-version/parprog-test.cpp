//9. Сортировка Шелла с четно-нечетным слиянием Бэтчера.
#include <iostream>
#include <cstdlib>
#include <cstdio>
//#include <vector>

using namespace std;

// Четно-нечетное слияние Бэтчера
/*template <typename T>
void compexch(T &a, T &b) {
    if (b < a)
      swap(a, b);
}

template <typename T>
void shuffle(vector<T> Arr, unsigned int start, unsigned int end_length) {
    auto half = (unsigned int) (start + end_length) / 2;
    vector<T> tmp(Arr.size());
    unsigned int i, j;
    for (i = start, j = 0; i <= end_length; i += 2, j++) {
        tmp[i] = Arr[start + j];
        tmp[i + 1] = Arr[half + j + 1];
    }
    for (auto i = 0; i < tmp.size(); i++)
       Arr[i] = tmp[i];
}

template <typename T>
void unshuffle(vector<T> Arr, unsigned int start, unsigned int end_length) {
    auto half = (unsigned int) (start + end_length) / 2;
    vector<T> tmp(Arr.size());
    unsigned int i, j;
    for (i = start, j =0; i<=end_length; i += 2, j++) {
        tmp[start + j] = Arr[i];
        tmp[half + j + 1] = Arr[i + 1];
    }
    for (auto i = 0; i < tmp.size(); i++)
        Arr[i]  = tmp[i];
}

template <typename T>
void OddEvenMergeSort(vector<T> Arr, unsigned int start, unsigned int end_length) {
    if (end_length == start + 1)
      compexch(Arr[start], Arr[end_length]); //мы дошли до подмассива размера 2 - теперь просто сравним элементы
    if (end_length < start + 2)
      return; //дошли до подмассива размера 1 - выходим, такой подмассив априори отсортирован
    unshuffle(Arr, start, end_length); //делим подмассив на две части
    auto half = (unsigned int) (start + end_length) / 2;
    OddEvenMergeSort(Arr, start, half);
    OddEvenMergeSort(Arr, half + 1, end_length); //вызываемся рекурсивно для половинок
    shuffle(Arr, start, end_length); //сливаем части
    for (auto i = start + 1; i < end_length; i += 2)
        compexch(Arr[i], Arr[i + 1]);
    auto halfSize = (end_length - start + 1) / 2 - 1;       //*
    for (int i = start + 1; i + halfSize < end_length; i++) //*
        compexch(Arr[i], Arr[i + halfSize]);    //*
}*/

// Сортировка Шелла
template <typename T>
void Shell_Sort(T *Arr, unsigned int length) {
  int distance; // Расстояние между элементами
  int i,j,temp;

  for(distance = length/2; distance > 0; distance /= 2)
    for(i = distance; i < length; i++)
      for(j = i - distance; j >= 0 && Arr[j] > Arr[j + distance]; j -= distance)
      {
        temp = Arr[j];
        Arr[j] = Arr[j + distance];
        Arr[j + distance] = temp;
      }
}

int main(int argc, char *argv[]) {
  if(argv[1] == NULL) {
    cout<<"Can't run the programm"<<endl;
    exit(-1);
  }

  int data;

  FILE* stdin = fopen("array_in.bin", "rb");
  FILE* stdout = fopen("array_out.bin", "wb");

  fread(&data, sizeof(data), 1, stdin);

  int *Arr = new int[data];

  fread(Arr,sizeof(*Arr), data, stdin);

  int length = atoi(argv[1]);
  int *Arr_Shell = new int [length];
  for (int p = 0; p < length; p++) {
    Arr_Shell[p] = rand()%1000000;
  }
  Shell_Sort(Arr_Shell, length);
  for(int i = 0; i < length; i++)
    cout <<"Shell Sort: "<<Arr_Shell[i] << endl;
  cout<<endl;

  fwrite(Arr,sizeof(*Arr),data,stdout);

  cout << "THE END" << endl;

  delete Arr_Shell;
  fclose(stdin);
  fclose(stdout);

  return 0;
}
