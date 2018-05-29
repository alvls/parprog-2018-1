double CCSMatrGet(double * A, int * IA, int * JA, int N, int i, int j) {
    double Value = 0;
    int N1 = JA[j];
    int N2 = JA[j + 1];
    for (int k = N1; k < N2; k++) {
        if (IA[k] == i) {
            Value = A[k];
            break;
        }
    }
    return Value;
}

void CCSMatrPut(double* &A, int* &IA, int* &JA, int N, int i, int j, double val) {
    bool zero_flag = true;
    int N1 = JA[j];
    int N2 = JA[j + 1];

    int k;
    for (k = N1; k < N2; k++) {
        if (IA[k] == i) {
            A[k] = val;
            zero_flag = false;
            break;
        }
    }

    if (zero_flag) {
        double * B = new double[JA[N] + 1];
        int * IB = new int[JA[N] + 1];
        int * JB = new int[N + 1];
        int f;

        for (f = 0; f < j + 1; f++)
            JB[f] = JA[f];

        for (f = j + 1; f < N + 1; f++)
            JB[f] = JA[f] + 1;

        for (f = 0; f < JB[j]; f++) {
            B[f] = A[f];
            IB[f] = IA[f];
        }

        for (f = JA[j]; f < JA[j + 1]; f++) {
            if (IA[f] < i) {
                B[f] = A[f];
                IB[f] = IA[f];
            }
            else {
                B[f] = val;
                IB[f] = i;
                break;
            }
        }

        if (f == JA[j + 1]) {
            B[f] = val;
            IB[f] = i;
        }
        else {
            f++;
            for (; f < JA[j + 1] + 1; f++) {
                B[f] = A[f - 1];
                IB[f] = IA[f - 1];
            }
        }

        for (f = JA[j + 1]; f < JA[N]; f++) {
            B[f + 1] = A[f];
            IB[f + 1] = IA[f];
        }

        delete[] A;
        delete[] IA;
        delete[] JA;
        A = B;
        IA = IB;
        JA = JB;
    }
}

int MaxValOfArr(int * arr, int size) {
    int buff;
    if (arr != nullptr)
        buff = arr[0];
    else
        throw "empty array of MaxValOfArr function";
    
    for (int i = 1; i < size; i++)
        if (buff < arr[i])
            buff = arr[i];
    
    return buff;
}

bool CCSMatrMultCheck(int * IB, int * JB,  int N) {
    if (MaxValOfArr(IB, JB[N]) > N)
        return false;
    else
        return true;
}
/*
bool ArrBinFind(int * arr, int size, int num) {
    int middle, left, right;
    left = 0; right = size - 1;
    while (true)
    {
        if (left > right) return false;
        middle = left + (right - left) / 2;
        if (arr[middle] < num) left = middle + 1;
        if (arr[middle] > num) right = middle - 1;
        if (arr[middle] == num) return true;
    }
} */
int ArrIndexFind(int *arr, int size, int start, int num) {
    for (int i = start; i < size; i++)
        if (arr[i] == num) return i;
    return -1;
}
/*
int CCSMatrMultValIC(double * A, int * IA, int * JA, double * B, int * IB, int * JB, int N) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int f = JA[i]; f < JA[i + 1]; f++)
            if (CCSMatrGet(B, IB, JB, N, i, IA[f]) != 0) count++;
    return count;
}
*/

int ColSearch(int * JA, int i) {
    int f;
    for (f = 0; !(JA[f + 1] > i); f++);
    return f;
}

void CCSMatrMult(double * A, int * IA, int * JA, double * B, int * IB, int * JB, double * &C, int * &IC, int * &JC, int N) {
    if (CCSMatrMultCheck(IB, JB, N)) {
        if (C != nullptr)
            delete[] C;
        if (IC != nullptr)
            delete[] IC;
        if (JC != nullptr)
            delete[] JC;

        JC = new int[N + 1];
        JC[N] = 0;
        for (int i = 0; i < N; i++) JC[i] = 0;
        /*    JC[N] = CCSMatrMultValIC(A, IA, JA, B, IB, JB, N);
            IC = new int[JC[N]];
            C = new double[JC[N]];
            for (int i = 0; i < N; i++)
                JC[i] = 0;
            for (int i = 0; i < JC[N]; i++) {
                IC[i] = 0;
                C[i] = 0;
            }
        */
        for (int i = 0; i < JA[N]; i++) {
            int buf, start = 0;
            while ((buf = ArrIndexFind(IB, JB[N], start, ColSearch(JA,i))) != -1) {
                CCSMatrPut(C, IC, JC, N, IA[i], ColSearch(JB, buf), CCSMatrGet(C, IC, JC, N, IA[i], ColSearch(JB, buf)) + A[i] * B[buf]);
                start = buf + 1;
            }
        }
    }
    else
        throw "matrix can not be multiple";
}