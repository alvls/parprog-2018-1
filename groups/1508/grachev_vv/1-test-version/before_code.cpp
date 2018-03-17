#include <cstdio>
#include <omp.h>

void MatrixMult(double *A, double *B, double *C, int n);

int main(int argc, char* argv[]){
    int n;
    double *A, *B, *C;
    if (argc > 1){
        freopen(argv[1], "rb", stdin);
    }
    else
        freopen("matr.in", "rb", stdin);
    freopen("matr.out", "wb", stdout);
    fread(&n, sizeof(n), 1, stdin);
    A = new double[n * n];
    B = new double[n * n];
    C = new double[n * n];

    fread(A, sizeof(*A), n * n, stdin);
    fread(B, sizeof(*B), n * n, stdin);    for (int i = 0; i < n * n; i++)
        C[i] = 0.0;

    double time = omp_get_wtime();
    MatrixMult(A, B, C, n);
    time = omp_get_wtime() - time;

    fwrite(&time, sizeof(time), 1, stdout);
    fwrite(C, sizeof(*C), n * n, stdout);

    delete A;
    delete B;
    delete C;

    return 0;
}