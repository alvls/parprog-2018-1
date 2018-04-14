#include <omp.h>
#include <math.h>


void InsertSort(double* arr, int i, int length, int half) {
    
    double temp = 0;
    int j = 0;
    for (int f = half + i; f < length; f = f + half)
    {
        j = f;
        while (j > i && arr[j - half] > arr[j])
        {
            temp = arr[j];
            arr[j] = arr[j - half];
            arr[j - half] = temp;
            j = j - half;
        }
    }
}

void shellSortParallel(double* array, int length)
{
    int h;
    int i = 0;
    for (h = length / 2; h > 0; h = h / 2)
    {
#pragma omp parallel for 
        for (i = 0; i < h; i++)
        { 
            InsertSort(array, i, length, h);
        }
    }
}
