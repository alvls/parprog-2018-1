#include <cstdlib>
#include <cstdio>
#include <omp.h>

int GetBlockSize(int n, int num_threads);
void MatrixMult(double *A, double *B, double *C, int n, int block_size);

int main(int argc, char* argv[]){
    int n, num_threads = 1;
    double *A, *B, *C;
    if (argc > 1)
        num_threads = atoi(argv[1]);
    if (argc > 2)
        freopen(argv[2], "rb", stdin);
    else
        freopen("matr.in", "rb", stdin);
    freopen("matr.out", "wb", stdout);
    fread(&n, sizeof(n), 1, stdin);

    A = new double[n * n];
    B = new double[n * n];
    C = new double[n * n];

    fread(A, sizeof(*A), n * n, stdin);
    fread(B, sizeof(*B), n * n, stdin);
    for (int i = 0; i < n * n; i++)
        C[i] = 0.0;

    omp_set_num_threads(num_threads);

    int block_size = GetBlockSize(n, num_threads);
    double time = omp_get_wtime();
    MatrixMult(A, B, C, n, block_size);
    time = omp_get_wtime() - time;

    fwrite(&time, sizeof(time), 1, stdout);
    fwrite(C, sizeof(*C), n * n, stdout);

    delete A;
    delete B;
    delete C;

    return 0;
}
