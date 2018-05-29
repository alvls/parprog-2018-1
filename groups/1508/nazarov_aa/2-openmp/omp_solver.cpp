#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>
#include <omp.h>
#include <random>

int main(int argc, char * argv[]) {
    if (argc != 4) {
        std::cout << "use '" << argv[0] << " [input file] [output file] [num threads]'" << std::endl;
        return 1;
    }
    int N, threads = atoi(argv[3]);
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

    int i, j, k, s, sum = 0, chunk = (N / 100 < 1) ? 1 : N / 100;
    int I_buff;
    double val_buff;
    int *col_val = new int[N];
    bool *vec;
    #pragma omp parallel shared(col_val, chunk, A, B, IA, IB, JA, JB, N, sum) private(i, j, k, vec) num_threads(threads)
    {
        vec = new bool[N];
        #pragma omp for schedule(static, chunk)
        for (i = 0; i < N; i++)
            col_val[i] = 0;

        #pragma omp for schedule(dynamic, chunk)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++)
                vec[j] = false;

            for (j = JB[i]; j < JB[i + 1]; j++) {
                for (k = JA[IB[j]]; k < JA[IB[j] + 1]; k++)
                    vec[IA[k]] = true;
            }

            for (j = 0; j < N; j++)
                if (vec[j]) col_val[i]++;
        }

        delete[] vec;
    }

    for (i = 0; i < N; i++)
        sum = sum + col_val[i];
    C = new double[sum];
    IC = new int[sum];
    JC = new int[N + 1];
    JC[0] = 0;
    for (i = 1; i < N + 1; i++) {
        JC[i] = JC[i - 1] + col_val[i - 1];
    }
    
    #pragma omp parallel for shared(C, IC, sum) private(i) schedule(static, chunk)
    for (i = 0; i < sum; i++) { 
        C[i] = 0.0;
        IC[i] = -1;
    }

    #pragma omp parallel shared(chunk, A, B, C, IA, IB, IC, JA, JB, JC, N) private(i, j, k, s, I_buff, val_buff) num_threads(threads)
    {
    #pragma omp for schedule(dynamic, chunk)
        for (i = 0; i < N; i++) {
            for (j = JB[i]; j < JB[i + 1]; j++) {
                for (k = JA[IB[j]]; k < JA[IB[j] + 1]; k++) {
                    for (s = JC[i]; s < JC[i + 1]; s++) {
                        if (IC[s] == IA[k]) {
                            C[s] += B[j] * A[k];
                            break;
                        }
                        if (IC[s] == -1) {
                            IC[s] = IA[k];
                            C[s] = A[k] * B[j];
                            break;
                        }
                    }
                }
            }
        }

    #pragma omp for schedule(dynamic, chunk)
        for (i = 0; i < N; i++) {
            for (j = JC[i]; j < JC[i + 1]; j++) {
                for (k = j + 1; k < JC[i + 1]; k++) {
                    if (IC[j] > IC[k]) {
                        I_buff = IC[j];
                        val_buff = C[j];
                        IC[j] = IC[k];
                        C[j] = C[k];
                        IC[k] = I_buff;
                        C[k] = val_buff;
                    }
                }
            }
        }
    }

    time = omp_get_wtime() - time;

    fwrite(&time, sizeof(time), 1, stdout);
    fwrite(&N, sizeof(N), 1, stdout);
    fwrite(JC, sizeof(*JC), N + 1, stdout);
    fwrite(IC, sizeof(*IC), JC[N], stdout);
    fwrite(C, sizeof(*C), JC[N], stdout);

    return 0;
}