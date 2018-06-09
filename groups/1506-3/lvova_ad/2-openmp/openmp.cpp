#include <omp.h>
#include <iostream>
#include <math.h>

void insert_sort(double* arr, int i, int length, int half);
void shell_sort(double* array, int length);
void merge_in_the_same_array(double* array, int m, int n, int it1, int it2);
void print_one_array(double* array, int length, int modi, int grain_size);
void shell_sort_with_a_shift(double* array, int iteration, int length);

void shell_parallel_openmp_sort(double* arr, int length, int n_threads)
{
    omp_set_num_threads(n_threads);
    int grain_size = 0;
    int modi = 0;
    int tail = 0;

    grain_size = length / (n_threads);
    modi = length % (n_threads);
    tail = modi + grain_size;

    std::cout << std::endl << std::endl;
    std::cout << "# length of array = " << length << std::endl;
    std::cout << "# threads = " << n_threads << std::endl;
    std::cout << "# grain size of array to sort by shell sorting = " << grain_size << std::endl;
    std::cout << "# last group = " << tail << std::endl;
    std::cout << "# modi = " << modi << std::endl;
    //
    if (length < 150)
    {
        std::cout << std::endl << "no sorting" << std::endl;
        print_one_array(arr, length, modi, grain_size);
    }
    //

#pragma omp parallel for schedule(static) shared(arr)
        for (int f = 0; f < n_threads; f++)
        {
            if (f == n_threads - 1)
            {
                shell_sort_with_a_shift(arr, f*grain_size, tail);
            }
            else
                shell_sort_with_a_shift(arr, f*grain_size, grain_size);
        }
    

    if (length < 150)
    {
        std::cout << std::endl << std::endl << "group sorting" << std::endl;
        print_one_array(arr, length, modi, grain_size);
        std::cout << std::endl;
    }
    //

    int k = 0;
    int i = 0;
    if (n_threads % 2 == 0)
        i = n_threads / 2;
    else
        i = n_threads / 2 + 1;
    omp_set_num_threads(i);
    for (i; i > 0;)
    {
        int start1 = 0, start2 = start1 + grain_size*pow(2, k);
        int m, n = 0;
        m = grain_size*pow(2, k);
        n = grain_size*pow(2, k);
        omp_set_num_threads(i);
#pragma omp parallel for schedule(static) shared(arr, n, m, start1, start2)
        
            for (int f = 0; f < n_threads; f++)
            {
                start1 = f*grain_size*pow(2, k + 1);
                start2 = start1 + grain_size*pow(2, k);
                if (start2 < length)
                {
                    if (start2 + 2 * n > length)
                    {
                        merge_in_the_same_array(arr, m, length - start2, start1, start2);
                        break;
                    }
                    else
                        merge_in_the_same_array(arr, m, n, start1, start2);
                }
            }
        
        k++;
        //
        if (length < 150)
        {
            std::cout << std::endl << "after " << i << " mergies -->" << std::endl;
            print_one_array(arr, length, modi, 2 * m);
            std::cout << std::endl;
        }
        //
        if (i == 1)
            i = 0;
        else
            if (i % 2 == 0)
                i = i / 2;
            else
                i = i / 2 + 1;
    }
}


void merge_in_the_same_array(double* array, int m, int n, int it1, int it2)
{
    int i = 0, j = 0, k = 0;
    int size = m + n;
    double* temp;
    temp = new double[size];

    while (i < m && j < n) {
        if (array[i + it1] <= array[j + it2]) {
            temp[k] = array[i + it1];
            i++;
        }
        else {
            temp[k] = array[j + it2];
            j++;
        }
        k++;
    }
    if (i < m) {
        for (int p = i; p < m; p++) {
            temp[k] = array[p + it1];
            k++;
        }
    }
    else {
        for (int p = j; p < n; p++) {
            temp[k] = array[p + it2];
            k++;
        }
    }

    for (i = it1; i < it2 + n; i++)
        array[i] = temp[i - it1];
}


void merge_2_arrays(double* A, double* B, int size_A, int size_B)
{
    int i = 0, j = 0, k = 0;
    int size = size_A + size_B;
    double* temp;
    temp = new double[size];

    while (i < size_A && j < size_B) {
        if (A[i] <= B[j]) {
            temp[k] = A[i];
            i++;
        }
        else {
            temp[k] = B[j];
            j++;
        }
        k++;
    }
    if (i < size_A) {
        for (int p = i; p < size_A; p++) {
            temp[k] = A[p];
            k++;
        }
    }
    else {
        for (int p = j; p < size_B; p++) {
            temp[k] = B[p];
            k++;
        }
    }

    for (i = 0; i < size_A + size_B; i++)
        A[i] = temp[i];
}


void print_one_array(double* array, int length, int modi, int grain_size)
{
    for (int i = 0; i < length - modi; i++)
    {
        if (i%grain_size == 0)
        {
            std::cout << std::endl << "* " << i << " * ";
        }
        std::cout << array[i] << " ";
    }
    for (int i = length - modi; i < length; i++)
    {
        std::cout << array[i] << " ";
    }
}


void print_n_arrays(double** temp, int n_threads, int grain_size, int tail, int k)
{
    int i = 0;
    for (i = 0; i < n_threads - 1; i++)
    {
        std::cout << "* " << i*k << " * ";
        for (int j = 0; j < grain_size; j++)
            std::cout << temp[i*k][j] << " ";
        std::cout << std::endl;
    }
    std::cout << "* " << i*k << " * ";
    for (int j = 0; j < tail; j++)
        std::cout << temp[(i)*k][j] << " ";
}