#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>

int main(int argc, char* argv[]) {

    freopen(argv[1], "rb", stdin);

    int len;
    int* arr;
    double time;

    fread(&time, sizeof(time), 1, stdin);
    fread(&len, sizeof(len), 1, stdin);

    arr = new int[len];
    fread(arr, sizeof(*arr), len, stdin);

    std::cout << "[LEN]: " << len;
    std::cout << "\n[SORTING TIME]: ";
    if (time < 0) {
        std::cout << "UNSORTED";
    }
    std::cout << time;
    std::cout << "\n[ARR]: { ";
    for (int i = 0; i < len; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << "\b\b }";

    delete[] arr;
    return 0;
}