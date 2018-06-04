#include <cstdio>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    if (argc > 1){
        FILE *bin;
        ofstream textin;
        bin = fopen(argv[1], "rb");
        textin.open("tmatr.in");
        
        int n;
        fread(&n, sizeof(n), 1, bin);
        textin << n << endl;
        double* A = new double[n];
        for (int k = 0; k < 2; k++)
            for (int i = 0; i < n; i++) {
                fread(A, sizeof(*A), n, bin);
                for (int j = 0; j < n; j++)
                    textin << A[j] << ' ';
                textin << endl;
            }
        fclose(bin);
        textin.close();
        delete A;
    }
    return 0;
}