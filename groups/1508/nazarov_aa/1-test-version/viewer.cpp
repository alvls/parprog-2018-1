#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {
    FILE* file_in = NULL;
    bool is_ans = false;
    if (argc != 2) throw "incorrect arg";
    if ((file_in = fopen(argv[1], "rb")) == NULL) {
        cout << argv[0] << " can't open file: " << argv[1] << endl;
        return 1;
    }
    for (int i = 0; argv[1][i] != '\0'; i++)
        if (argv[1][i] == '.') { is_ans = true; break; }
    if (!is_ans) {
        int N;
        int *JA, *JB, *IA, *IB;
        double *A, *B;

        fread(&N, sizeof(N), 1, file_in);
        JA = new int[N + 1];
        JB = new int[N + 1];
        fread(JA, sizeof(*JA), N + 1, file_in);
        fread(JB, sizeof(*JB), N + 1, file_in);
        IA = new int[JA[N]];
        IB = new int[JB[N]];
        A = new double[JA[N]];
        B = new double[JB[N]];
        fread(IA, sizeof(*IA), JA[N], file_in);
        fread(IB, sizeof(*IB), JB[N], file_in);
        fread(A, sizeof(*A), JA[N], file_in);
        fread(B, sizeof(*B), JB[N], file_in);

        cout << "N: " << N << endl;
        cout << "JA: ";
        for (int i = 0; i < N + 1; i++)
            cout << JA[i] << " ";
        cout << endl << "IA: ";
        for (int i = 0; i < JA[N]; i++)
            cout << IA[i] << " ";
        cout << endl << "A: ";
        for (int i = 0; i < JA[N]; i++)
            cout << A[i] << " ";
        cout << endl << "JB: ";
        for (int i = 0; i < N + 1; i++)
            cout << JB[i] << " ";
        cout << endl << "IB: ";
        for (int i = 0; i < JB[N]; i++)
            cout << IB[i] << " ";
        cout << endl << "B: ";
        for (int i = 0; i < JB[N]; i++)
            cout << B[i] << " ";
        cout << endl;
    }
    else {
        int N;
        int *JA, *IA;
        double *A;
        double time;

        fread(&time, sizeof(double), 1, file_in);
        fread(&N, sizeof(N), 1, file_in);
        JA = new int[N + 1];
        fread(JA, sizeof(*JA), N + 1, file_in);
        IA = new int[JA[N]];
        A = new double[JA[N]];
        fread(IA, sizeof(*IA), JA[N], file_in);
        fread(A, sizeof(*A), JA[N], file_in);

        cout << "N: " << N << endl;
        cout << "time: " << time << endl;
        cout << "JA: ";
        for (int i = 0; i < N + 1; i++)
            cout << JA[i] << " ";
        cout << endl << "IA: ";
        for (int i = 0; i < JA[N]; i++)
            cout << IA[i] << " ";
        cout << endl << "A: ";
        for (int i = 0; i < JA[N]; i++)
            cout << A[i] << " ";
        cout << endl;
    }
    return 0;
}
