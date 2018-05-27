#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>

void CCSMatrPut(double* &A, int* &IA, int* &JA, int N, int i, int j, double val);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "use '" << argv[0] << " [input file] [output file]'" << std::endl;
        return 0;
    }

    freopen(argv[1], "rb", stdin);
    freopen(argv[2], "wb", stdout);

    char buffer[255];

    fgets(buffer, 255, stdin);
    for (int i = 0; buffer[i] != '\0'; i++)
        if (buffer[i] == '\n') buffer[i] = '\0';
    int N = atoi(buffer);
    double *A = nullptr, *B = nullptr;
    int *IA = nullptr, *IB = nullptr; 
    int *JA = new int[N + 1];
    int *JB = new int[N + 1];

    for (int i = 0; i < N + 1; i++) {
        JA[i] = 0;
        JB[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        fgets(buffer, 255, stdin);
        int val = 0;
        int power = 0;
        for (int k = 0, j = 0; buffer[k] != '\n'; k++) {
            if (buffer[k] == ' ' || buffer[k + 1] == '\n') {
                if (val != 0) { CCSMatrPut(A, IA, JA, N, i, j, val); val = 0; };
                j++;
                power = 0;
            }
            else {
                val += (buffer[k] - '0') * pow(10, power);
                power++;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        fgets(buffer, 255, stdin);
        int val = 0;
        int power = 0;
        for (int k = 0, j = 0; buffer[k] != '\n'; k++) {
            if (buffer[k] == ' ' || buffer[k + 1] == '\n') {
                if (val != 0) { CCSMatrPut(B, IB, JB, N, i, j, val); val = 0; };
                j++;
                power = 0;
            }
            else {
                val += (buffer[k] - '0') * pow(10, power);
                power++;
            }
        }
    }

    fwrite(&N, sizeof(N), 1, stdout);
    fwrite(JA, sizeof(*JA), N + 1, stdout);
    fwrite(JB, sizeof(*JB), N + 1, stdout);
    fwrite(IA, sizeof(*IA), JA[N], stdout);
    fwrite(IB, sizeof(*IB), JB[N], stdout);
    fwrite(A, sizeof(*A), JA[N], stdout);
    fwrite(B, sizeof(*B), JB[N], stdout);

    return 0;
}