#define _CRT_SECURE_NO_WARNINGS

#include <cstdio> 
#include <random> 
#include <ctime> 
#include <chrono>
#include <iostream>

const int len_tests[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 100, 101, 1000, 1001, 10000, 10001, 100000, 100001, 1000000, 1000001, 10000000, 100000001, 100000000, 100000001};
const int max_val = INT16_MAX;
const double fict_time = -1.0;

int main(int argc, char * argv[])
{
    if (argc != 2 || atoi(argv[1]) < 1 || atoi(argv[1]) > 25) {
        std::cout << "\tARRAY GENERATOR PROGRAM\n";
        std::cout << "Use the following pattern to use the program:\n";
        std::cout << "\"generator [number of test length (1 - 25)]\"";
        return 1;
    }

    int len = len_tests[atoi(argv[1]) - 1];

    freopen(argv[1], "wb", stdout);
    std::default_random_engine generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution <int> distribution(0, max_val);

    fwrite(&len, sizeof(double), 1, stdout);
    fwrite(&len, sizeof(len), 1, stdout);
    
    int *arr = new int[len];

    for (int i = 0; i < len; i++) {
        arr[i] = distribution(generator);
    }

    fwrite(arr, sizeof(*arr), len, stdout);

    delete[] arr;
    return 0;
}