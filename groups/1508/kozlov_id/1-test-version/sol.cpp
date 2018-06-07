int getMax(const int* arr, const int len) {
    int max_val = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

void countSort(int* arr, int len, int exp) {
    int* tmparr = new int[len];
    int i, count[10] = { 0 };

    for (i = 0; i < len; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (i = len - 1; i >= 0; i--) {
        tmparr[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < len; i++) {
        arr[i] = tmparr[i];
    }

    delete[] tmparr;
}

void RadixSort(int* arr, const int len) {

    int max_val = getMax(arr, len);

    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        countSort(arr, len, exp);
    }
}
