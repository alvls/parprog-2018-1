#include <cstdio>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    if (argc > 1){
        FILE *bin;
        ifstream textin;
        bin = fopen(argv[1], "wb");
        textin.open("tmatr.in");

        int n;
        textin >> n;
        fwrite(&n, sizeof(n), 1, bin);
        double* A = new double[n];
        for (int k = 0; k < 2; k++)
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    textin >> A[j];
                fwrite(A, sizeof(*A), n, bin);
            }
        fclose(bin);
        textin.close();
        delete A;
    }
    return 0;
}