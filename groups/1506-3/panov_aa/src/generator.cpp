#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include <iostream>
using namespace std;
int n_tests[] = { 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 100, 200, 300, 400, 500,
600, 700, 800, 900, 1000 };
int main(int argc, char * argv[])
{
    string path = "./tests/";
    string output = "matr";
    string number = "";
    string extensionOut = ".in";
    if (argc == 2)
    {
        number = argv[1];
        output = "";        
    }
    else
    {
        if (argc > 2)
        {
            number = argv[1];
            output = argv[2];           
        }
    }

    freopen((path + output + number + extensionOut).c_str(), "wb", stdout);

    // создаём генератор случайных чисел с seed равным количеству времени с начала эпохи
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    // создаём равномерное распределение случайной величины типа double в диапазоне
    // [-10000, 10000]
    uniform_int_distribution <int> distribution(-100, 100);
    // задаём размер матриц
    int n = 10;
    // если передали номер теста в аргументах командной строки, то берём размер из n_tests
    if (argc > 1)
        n = n_tests[atoi(argv[1])];
    // записываем в бинарном виде размерность матриц
    fwrite(&n, sizeof(n), 1, stdout);
    // создаём временный массив для строки матрицы
    int * cur = new int[n];
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