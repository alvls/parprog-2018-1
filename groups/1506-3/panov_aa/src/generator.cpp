#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
using namespace std;
int n_tests[] = { 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 100, 200, 300, 400, 500,
600, 700, 800, 900, 1000 };
int main(int argc, char * argv[])
{
    // перенаправляем поток stdout в файл matr.in
    freopen("matr.in", "wb", stdout);
    // создаём генератор случайных чисел с seed равным количеству времени с начала эпохи
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    // создаём равномерное распределение случайной величины типа double в диапазоне
    // [-10000, 10000]
    uniform_real_distribution <double> distribution(-1e4, 1e4);
    // задаём размер матриц
    int n = 1000;
    // если передали номер теста в аргументах командной строки, то берём размер из n_tests
    if (argc > 1)
        n = n_tests[atoi(argv[1])];
    // записываем в бинарном виде размерность матриц
    fwrite(&n, sizeof(n), 1, stdout);
    // создаём временный массив для строки матрицы
    double * cur = new double[n];
    // генерируем первую матрицу
    for (int i = 0; i < n; i++)
    {
        // заполняем случайными числами из равномерного распределения очередную строку матрицы
        for (int j = 0; j < n; j++)
            cur[j] = distribution(generator);
        // записываем строку в бинарном виде в файл
        fwrite(cur, sizeof(*cur), n, stdout);
    }
    // аналогично генерируем вторую матрицу
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cur[j] = distribution(generator);
        fwrite(cur, sizeof(*cur), n, stdout);
    }
    return 0;
}