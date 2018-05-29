#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <iostream>
#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>

#define TESTS_NUM 17

using namespace std;
// 1 число - размер матрицы, 2 число - процент "заполненности" матрицы
int n_tests[][2] = { { 6, 1},{ 10, 1 },{ 100, 1 },{ 1000, 1 },{ 6, 5 },{ 10, 5 },{ 100, 5 },{ 1000, 5 },
{ 6, 25 },{ 10, 25 },{ 100, 25 },{ 1000,25 } ,{ 6, 50 },{ 10, 50 },{ 100, 50 },{ 1000, 50 }, {40000, 1} };

void test_creator(int i) {
    if (i < 0 || i > 20)
        throw "wrong test number";
    char buff[3];
    freopen(itoa(i, buff, 10), "wb", stdout);

    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_real_distribution <double> val_distribution(-10, 10);

    int n = n_tests[i][0];
    int proc = n_tests[i][1];

    double *A, *B;
    int *IA, *IB, *JA, *JB;

    JA = new int[n + 1];
    JB = new int[n + 1];
    int num_of_val = static_cast<int>(static_cast<double>(static_cast<double>(n*n) / 100.0)*n_tests[i][1]);
    if (num_of_val == 0)
        num_of_val = 1;
    IA = new int[num_of_val];
    IB = new int[num_of_val];
    A = new double[num_of_val];
    B = new double[num_of_val];

    int A_begin = 0, B_begin = 0;
    int A_end = ((num_of_val / n) == 0) ? 1 : num_of_val / n;
    int B_end = A_end;

    JA[0] = 0; JA[n] = num_of_val;
    JB[0] = 0; JB[n] = num_of_val;

    for (int f = 1; f < n; f++) {
        uniform_int_distribution <int> JA_distribution(A_begin, (A_end * f > num_of_val) ? num_of_val : A_end*f);
        uniform_int_distribution <int> JB_distribution(B_begin, (B_end * f > num_of_val) ? num_of_val : B_end*f);

        A_begin = JA_distribution(generator);
        B_begin = JB_distribution(generator);

        JA[f] = A_begin;
        JB[f] = B_begin;
    }

    for (int f = n; f > 0; f--) {
        if (JA[f] - JA[f - 1] > n)
            JA[f - 1] = JA[f] - n;
        if (JB[f] - JB[f - 1] > n)
            JB[f - 1] = JB[f] - n;
    }

    for (int f = 0; f < n; f++) {
        int A_size = JA[f + 1] - JA[f];
        int B_size = JB[f + 1] - JB[f];
        for (int g = JA[f], begin = 0; g < JA[f + 1]; g++, begin++) {
            uniform_int_distribution <int> IA_distribution(begin, n - (JA[f + 1] - g));
            begin = IA_distribution(generator);
            IA[g] = begin;
        }
        for (int g = JB[f], begin = 0; g < JB[f + 1]; g++, begin++) {
            uniform_int_distribution <int> IB_distribution(begin, n - (JB[f + 1] - g));
            begin = IB_distribution(generator);
            IB[g] = begin;
        }
    }

    for (int f = 0; f < num_of_val; f++) {
        A[f] = val_distribution(generator);
        B[f] = val_distribution(generator);
    }

        fwrite(&n, sizeof(n), 1, stdout);
        fwrite(JA, sizeof(*JA), n + 1, stdout);
        fwrite(JB, sizeof(*JB), n + 1, stdout);
        fwrite(IA, sizeof(*IA), num_of_val, stdout);
        fwrite(IB, sizeof(*IB), num_of_val, stdout);
        fwrite(A, sizeof(*A), num_of_val, stdout);
        fwrite(B, sizeof(*B), num_of_val, stdout);

        delete[] JA;
        delete[] JB;
        delete[] IA;
        delete[] IB;
        delete[] A;
        delete[] B;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        for (int i = 0; i < TESTS_NUM; i++) {
            test_creator(i);
        }
    }
    else {
        test_creator(atoi(argv[1]));
    }
    return 0;
}