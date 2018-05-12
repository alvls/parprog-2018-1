#include <cstdlib>
#include <cstdio>
#include <tbb/tbb.h>

int GetBlockSize(int n, int num_threads);
void MatrixMult(double *A, double *B, double *C, int n, int block_size, int num_threads);

using namespace tbb;

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

    int block_size = GetBlockSize(n, num_threads);
    tick_count start_time = tick_count::now();
    MatrixMult(A, B, C, n, block_size, num_threads);
    tick_count end_time = tick_count::now();
    double time = (end_time - start_time).seconds();

    fwrite(&time, sizeof(time), 1, stdout);
    fwrite(C, sizeof(*C), n * n, stdout);

    delete A;
    delete B;
    delete C;

    return 0;
}
