#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>
#include <omp.h>
#include <random>

void CCSMatrMult(double* A, int* IA, int* JA, double* B, int* IB, int* JB, double* &C, int* &IC, int* &JC, int N);

int main(int argc, char * argv[]) {
    if (argc != 3) {
        std::cout << "use '" << argv[0] << " [input file] [output file]'" << std::endl;
        return 1;
    }
    int N;
    double *A, *B, *C;
    int *IA, *JA, *IB, *JB, *IC, *JC;

    C = nullptr;
    IC = nullptr;
    JC = nullptr;

    freopen(argv[1], "rb", stdin);
    freopen(argv[2], "wb", stdout);
    // Структура хранения в файле: Сначала идет N, потом JA, JB, потом IA, IB, потом A,B
    fread(&N, sizeof(N), 1, stdin);
    
    JA = new int[N + 1];
    JB = new int[N + 1];

    fread(JA, sizeof(*JA), N + 1, stdin);
    fread(JB, sizeof(*JB), N + 1, stdin);

    A = new double[JA[N]];
    B = new double[JB[N]];
    IA = new int[JA[N]];
    IB = new int[JB[N]];

    fread(IA, sizeof(*IA), JA[N], stdin);
    fread(IB, sizeof(*IB), JB[N], stdin);
    fread(A, sizeof(*A), JA[N], stdin);
    fread(B, sizeof(*B), JB[N], stdin);

    double time = omp_get_wtime();
    CCSMatrMult(A, IA, JA, B, IB, JB, C, IC, JC, N);
    time = omp_get_wtime() - time;

    fwrite(&time, sizeof(time), 1, stdout);
    fwrite(&N, sizeof(N), 1, stdout);
    fwrite(JC, sizeof(*JC), N + 1, stdout);
    fwrite(IC, sizeof(*IC), JC[N], stdout);
    fwrite(C, sizeof(*C), JC[N], stdout);

    return 0;
}