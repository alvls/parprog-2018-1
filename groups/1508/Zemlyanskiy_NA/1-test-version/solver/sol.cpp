#include <omp.h>

// Сортировка Шелла
template <typename T>
void Shell_Sort(T *Arr, unsigned int length) {
  int distance; // Расстояние между элементами
  int i,j,temp;
  #pragma omp parallel for num_threads(1)
  for(distance = length/2; distance > 0; distance /= 2)
    for(i = distance; i < length; i++)
      for(j = i - distance; j >= 0 && Arr[j] > Arr[j + distance]; j -= distance)
      {
        temp = Arr[j];
        Arr[j] = Arr[j + distance];
        Arr[j + distance] = temp;
      }
}
