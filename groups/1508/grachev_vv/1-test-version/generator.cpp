#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>

using namespace std;

int n_tests[] = { 1, 2, 2, 16, 16, 32, 32, 64, 64, 81, 81, 128, 128, 
                  256, 256, 256, 512, 512, 1024, 1024 };

int main(int argc, char* argv[]){
    freopen("matr.in", "wb", stdout);
    default_random_engine generator(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
    uniform_real_distribution <double> distribution(-1e4, 1e4);
    
    int n = 1024;
    if (argc > 1)
        n = n_tests[atoi(argv[1])];
    fwrite(&n, sizeof(n), 1, stdout);

    double* A = new double[n];

    for (int k = 0; k < 2; k++)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                A[j] = distribution(generator);
            fwrite(A, sizeof(*A), n, stdout);
        }

    delete A;
    return 0;
}
