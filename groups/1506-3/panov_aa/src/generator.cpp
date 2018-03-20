#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include <iostream>
#include "../include/matrix.h"
using namespace std;
int n_tests[] = { 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 100, 200, 300, 400, 500,
600, 700, 800, 900, 1000 };
Matrix getRandMatrix(int n, default_random_engine &generator, uniform_real_distribution<double> &distribution)
{
    Matrix m1(n, n);
    for (int i = 0; i < n*n; i++)
    {
        // заполняем случайными числами из равномерного распределения матрицу
        m1.vv[i] = distribution(generator);
    }
    return m1;
}
int main(int argc, char * argv[])
{
    string path = "./";
    string output = "matr";
    string number = "";
    string extensionIn = ".in";
    string extensionOutAnswer = ".ans";

    // задаём размер матриц
    // если передали номер теста в аргументах командной строки, то берём размер из n_tests
    int n = 10;
    if (argc > 1)
    {
        path = argv[1];
        path += "/";
        if (argc > 2)
        {
            int ind = atoi(argv[2]);
            n = n_tests[ind];
            if (argc > 3)
            {
                number = argv[3];
                output = "";
                if (argc > 4)
                {
                    output = argv[4];
                }
            }
        }
    }

    freopen((path + output + number + extensionIn).c_str(), "wb", stdout);
    // создаём генератор случайных чисел с seed равным количеству времени с начала эпохи
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    // создаём равномерное распределение случайной величины типа double в диапазоне
    // [-10, 10]
    uniform_real_distribution <double> distribution(-1e1, 1e1);
  
    // записываем в бинарном виде размерность матриц
    fwrite(&n, sizeof(n), 1, stdout);
    // генерируем первую матрицу
    Matrix m1 = getRandMatrix(n, generator, distribution);
    fwrite(m1.getP(), sizeof(m1.vv[0]), n*n, stdout);
    // генерируем вторую матрицу
    Matrix m2 = getRandMatrix(n, generator, distribution);
    fwrite(m2.getP(), sizeof(m2.vv[0]), n*n, stdout);

    // генерируем ответ
    Matrix ans = m1*m2;
    freopen((path + output + number + extensionOutAnswer).c_str(), "wb", stdout);
    fwrite(&n, sizeof(n), 1, stdout);
    fwrite(ans.getP(), sizeof(Element), n*n, stdout);
    return 0;
}