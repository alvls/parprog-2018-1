#include <omp.h>
#include <vector>

using namespace std;

// Сортировка Шелла
template <typename T>
void Shell_Sort(T *Arr, unsigned int length, unsigned int num_threads) {
  int distance; // Расстояние между элементами
  int i,j,temp;
  omp_set_num_threads(num_threads);
  for(distance = length/2; distance > 0; distance /= 2) {
    #pragma omp parallel
    {
      #pragma omp parallel for
      for(i = distance; i < length; i++) {
        for(j = i - distance; j >= 0 && Arr[j] > Arr[j + distance]; j -= distance)
        {
          temp = Arr[j];
          Arr[j] = Arr[j + distance];
          Arr[j + distance] = temp;
        }
      }
    }
  }
}
