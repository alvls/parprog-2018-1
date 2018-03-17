#include <iostream>
#include <random>
#include <chrono>
#include <omp.h>
#include "solver.h"

int main(int argc, char * argv[]) {
    Task testTask;
    Point answer;
    FILE * testFile;
    FILE * answerFile;
    std::string testFileName, answerFileName;
    int countOfTests;
    double time, tmp;

    if (argc == 0) {
        std::cout << "Error: Invalid count of tests" << std::endl;
        return 0;
    }

    countOfTests = atoi(argv[1]);

    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

    //Число различных функций - 20, но значений может быть 21,
    //для того, чтобы проверить алгоритм на неверно заданную функцию.
    //В качестве 21 функции выступает значение NAN.
    std::uniform_int_distribution<int> distFunc(0, 20);

    std::uniform_int_distribution<int> distIter(100, 10000);
    std::uniform_int_distribution<int> distR(1, 10);
    std::uniform_int_distribution<int> distEps(2, 6);
    std::uniform_real_distribution<double> distX(-100.0, 100.0);

    for (int i = 1; i <= countOfTests; ++i) {
        testTask.funcNum = distFunc(generator);
        testTask.maxOfIterations = distIter(generator);
        testTask.xl = distX(generator);
        testTask.xr = distX(generator);
        testTask.eps = pow(0.1, distEps(generator));
        testTask.r = distR(generator);

        if (testTask.xl > testTask.xr) {
            tmp = testTask.xl;
            testTask.xl = testTask.xr;
            testTask.xr = tmp;
        }

        testFileName = "tests/" + std::to_string(i);
        testFile = fopen(testFileName.c_str(), "wb");
        fwrite(&testTask, sizeof(testTask), 1, testFile);

        time = omp_get_wtime();
        answer = CalculateOptimum(&testTask);
        time = (omp_get_wtime() - time);

        answerFileName = "tests/" + std::to_string(i)+".ans";
        answerFile = fopen(answerFileName.c_str(), "wb");
        fwrite(&answer, sizeof(answer), 1, answerFile);

        fclose(testFile);
        fclose(answerFile);
    }

    return 0;
}
