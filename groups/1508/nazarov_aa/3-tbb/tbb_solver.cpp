#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>
#include <omp.h>
#include <random>
#include <tbb/tbb.h>

using namespace tbb;

struct CCSmatrix {
    double* Vals;
    int* I;
    int* J;
    int N;
};

void tbb_ccsmult(CCSmatrix A, CCSmatrix B, CCSmatrix &C, int threads) {
    int grainSize = (A.N / 100 < 1) ? 1 : A.N / 100;
    int *col_val = new int[A.N];
    for (int i = 0; i < A.N; i++)
        col_val[i] = 0;

    task_scheduler_init init(threads);
    parallel_for(blocked_range<int>(0, A.N, grainSize), [&](blocked_range<int> range) {
        bool *vec = new bool[A.N];
        int i, j, k;
        for (i = range.begin(); i < range.end(); i++) {
            for (j = 0; j < A.N; j++)
                vec[j] = false;

            for (j = B.J[i]; j < B.J[i + 1];j++)
                for (k = A.J[B.I[j]]; k < A.J[B.I[j] + 1]; k++)
                    vec[A.I[k]] = true;

            for (j = 0; j < A.N; j++)
                if (vec[j]) col_val[i]++;

        }
        delete[] vec;
    });

    int sum = 0;
    for (int i = 0; i < A.N; i++)
        sum += col_val[i];
    C.Vals = new double[sum];
    C.I = new int[sum];
    C.J = new int[C.N + 1];
    C.J[0] = 0;
    for (int i = 1; i < C.N + 1; i++) 
        C.J[i] = C.J[i - 1] + col_val[i - 1];

    delete[] col_val;

    for (int i = 0; i < sum; i++) {
        C.Vals[i] = 0.0;
        C.I[i] = -1;
    }

    parallel_for(blocked_range<int>(0, C.N, grainSize), [&](blocked_range<int> range) {
        int i, j, k, s;
        for (i = range.begin(); i < range.end(); i++)
            for (j = B.J[i]; j < B.J[i + 1]; j++)
                for(k = A.J[B.I[j]]; k < A.J[B.I[j] + 1]; k++)
                    for (s = C.J[i]; s < C.J[i + 1]; s++) {
                        if (C.I[s] == A.I[k]) {
                            C.Vals[s] += B.Vals[j] * A.Vals[k];
                            break;
                        }
                        if (C.I[s] == -1) {
                            C.I[s] = A.I[k];
                            C.Vals[s] = A.Vals[k] * B.Vals[j];
                            break;
                        }
                    }

    });

    parallel_for(blocked_range<int>(0, C.N, grainSize), [&](blocked_range<int> range) {
        int i, j, k;
        int I_buff;
        double val_buff;
        for (i = range.begin(); i < range.end(); i++)
            for (j = C.J[i]; j < C.J[i + 1]; j++)
                for (k = j + 1; k < C.J[i + 1]; k++)
                    if (C.I[j] > C.I[k]) {
                        I_buff = C.I[j];
                        val_buff = C.Vals[j];
                        C.I[j] = C.I[k];
                        C.Vals[j] = C.Vals[k];
                        C.I[k] = I_buff;
                        C.Vals[k] = val_buff;
                    }
    });

    init.terminate();
}

int main(int argc, char * argv[]) {
    if (argc != 4) {
        std::cout << "use '" << argv[0] << " [input file] [output file] [num threads]'" << std::endl;
        return 1;
    }
    int threads = atoi(argv[3]);
    CCSmatrix A, B, C;

    C.Vals = nullptr;
    C.I = nullptr;
    C.J = nullptr;

    freopen(argv[1], "rb", stdin);
    freopen(argv[2], "wb", stdout);
    // Структура хранения в файле: Сначала идет N, потом JA, JB, потом IA, IB, потом A,B
    fread(&A.N, sizeof(A.N), 1, stdin);
    B.N = C.N = A.N;
    A.J = new int[A.N + 1];
    B.J = new int[B.N + 1];

    fread(A.J, sizeof(*A.J), A.N + 1, stdin);
    fread(B.J, sizeof(*B.J), B.N + 1, stdin);

    A.Vals = new double[A.J[A.N]];
    B.Vals = new double[B.J[B.N]];
    A.I = new int[A.J[A.N]];
    B.I = new int[B.J[B.N]];

    fread(A.I, sizeof(*A.I), A.J[A.N], stdin);
    fread(B.I, sizeof(*B.I), B.J[B.N], stdin);
    fread(A.Vals, sizeof(*A.Vals), A.J[A.N], stdin);
    fread(B.Vals, sizeof(*B.Vals), B.J[B.N], stdin);

    tbb::tick_count t = tbb::tick_count::now();
    tbb_ccsmult(A, B, C, threads);
    double time = (tbb::tick_count::now() - t).seconds();

    fwrite(&time, sizeof(time), 1, stdout);
    fwrite(&C.N, sizeof(C.N), 1, stdout);
    fwrite(C.J, sizeof(*C.J), C.N + 1, stdout);
    fwrite(C.I, sizeof(*C.I), C.J[C.N], stdout);
    fwrite(C.Vals, sizeof(*C.Vals), C.J[C.N], stdout);

    return 0;
}