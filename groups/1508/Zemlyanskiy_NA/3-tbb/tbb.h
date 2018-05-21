#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

using namespace tbb;

// Сортировка Шелла
void Shell_Sort(int *Arr, unsigned int length) {
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

class EvenPartition:public task {
private:
    int *arr;
    int length1;
    int length2;
public:
    EvenPartition(int* _arr, int _length1,
                 int _length2): arr(_arr),
        length1(_length1), length2(_length2)
    {}
    task* execute() {
        int *arr2 = arr + length1;

        int length = (length1 + length2 + 1) / 2;
        int *temp = new int[length];

        int a = 0;
        int b = 0;
        int i = 0;
        while( (a < length1) && (b < length2)) {
            if(arr[a] <= arr2[b]) {
                temp[i] = arr[a];
                a += 2;
            }
            else {
                temp[i] = arr2[b];
                b += 2;
            }
            i++;
        }
        if (a >= length1)
            for(int j = b; j < length2; j += 2,i++)
                temp[i] = arr2[j];
        else
            for(int j = a; j < length1; j += 2,i++)
                temp[i] = arr[j];

        for (int j = 0;j < length; ++j)
          arr[j * 2] = temp[j];

        return NULL;
    }
};

class OddPartition:public task {
private:
    int *arr;
    int length1;
    int length2;
public:
    OddPartition(int* _arr, int _length1,
                int _length2): arr(_arr),
        length1(_length1), length2(_length2)
    {}
    task* execute() {
        int *arr2 = arr + length1;

        int length = (length1 + length2) - (length1 + length2 + 1) / 2;
        int *temp = new int[length];

        int a = 1;
        int b = 1;
        int i = 0;
        while( (a < length1) && (b < length2)) {
            if(arr[a] <= arr2[b]) {
                temp[i] = arr[a];
                a += 2;
            }
            else {
                temp[i] = arr2[b];
                b += 2;
            }
            i++;
        }
        if (a >= length1)
            for(int j = b; j < length2; j += 2,i++)
                temp[i] = arr2[j];
        else
            for(int j=a; j < length1; j+=2,i++)
                temp[i] = arr[j];
        for (int j = 0; j < length; ++j)
          arr[j * 2 + 1] = temp[j];

        return NULL;
    }
};

class Balancer {
private:
    int *arr;
public:
    Balancer(int *_arr):arr(_arr){}

    void operator()(const blocked_range<int>& r) const {
      int begin = r.begin(), end = r.end();
      for(int i = begin; i < end; i++)
        if(arr[i-1] > arr[i]) {
          int temp = arr[i - 1];
          arr[i - 1] = arr[i];
          arr[i] = temp;
        }
    }
};

class Sorter: public task {
private:
    int *arr;
    int length;
    int piece;

public:
    Sorter(int *_arr, int _length, int _piece) : arr(_arr), length(_length), piece(_piece) {}

    task* execute() {
        if (length <= piece) {
            Shell_Sort(arr, length);
        }
        else {
            int s = length / 2 + (length / 2) % 2;
            Sorter &sorter1 = *new (allocate_child()) Sorter(arr, s, piece);
            Sorter &sorter2 = *new (allocate_child()) Sorter(arr + s, length - s, piece);
            set_ref_count(3);
            spawn(sorter1);
            spawn_and_wait_for_all(sorter2);
            EvenPartition &evenPartition = *new (allocate_child()) EvenPartition(arr, s, length - s);
            OddPartition &oddPartition = *new (allocate_child()) OddPartition(arr, s, length - s);
            set_ref_count(3);
            spawn(evenPartition);
            spawn_and_wait_for_all(oddPartition);

            parallel_for(blocked_range<int>(1, length), Balancer(arr));
        }
        return NULL;
    }
};

void tbb_Shell_Sort(int *arr, int length, int threads) {
  task_scheduler_init init(threads);
	int piece = length / threads + 1;
	Sorter& sorter = *new (task::allocate_root())
		Sorter(arr, length, piece);
	task::spawn_root_and_wait(sorter);
}
