#include <tbb/tbb.h>

using namespace tbb;

int GetBlockSize(int n, int num_threads){ 
    int q = 1; 
    while ((q*q != num_threads) && (q*q < num_threads / 2 + 1)) 
        q++; 
    return n / q;
}

class MatrixMultiplicator{
private:
    const double *A, *B;
    double *const C;
    int const n;
public:
    MatrixMultiplicator(double *_A, double *_B, double *_C, int size) : A(_A), B(_B), C(_C), n(size){}
    void operator()(const blocked_range2d<int, int>& r) const
    {
        int r_begin = r.rows().begin(), r_end = r.rows().end();
        int c_begin = r.cols().begin(), c_end = r.cols().end();
        double temp;

        for (int i = r_begin; i < r_end; ++i)
            for (int j = c_begin; j < c_end; j++){
                temp = 0.0;
                for (int k = 0; k < n; k++)
                    temp += A[i*n + k] * B[k * n + j];
                C[i*n + j] += temp;
            }
    }
};

void MatrixMult(double *A, double *B, double *C, int n, int block_size, int num_threads){
    task_scheduler_init init(num_threads);
    parallel_for(blocked_range2d<int>(0, n, block_size, 0, n, block_size),
        MatrixMultiplicator(A, B, C, n));
}
