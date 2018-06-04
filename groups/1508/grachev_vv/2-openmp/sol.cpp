#include <omp.h>
#include <cstdio>

int GetBlockSize(int n, int num_threads){ 
    int q = 1; 
    while ((q*q != num_threads) && (q*q < num_threads / 2 + 1)) 
        q++; 
    return n / q;
}

void MatrixMult(double *A, double *B, double *C, int n, int block_size){
    int i, j, k, jj, kk;
    double temp;

    #pragma omp parallel shared(A, B, C, n) private(i, j, k, jj, kk, temp)
    {
        #pragma omp for schedule (static)
        for (jj = 0; jj < n; jj += block_size)
            for (kk = 0; kk < n; kk += block_size)
                for (i = 0; i < n; i++)
                    for (j = jj; j < ((jj + block_size) > n ? n : (jj + block_size)); j++)
                    {
                        temp = 0.0;
                        for (k = kk; k < ((kk + block_size) > n ? n : (kk + block_size)); k++)
                            temp += A[i*n + k] * B[k*n + j];
                        C[i*n + j] += temp;
                    }
    }

}