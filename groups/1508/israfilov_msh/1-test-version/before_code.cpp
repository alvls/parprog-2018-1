#include <omp.h>
#include <iostream>
#include "solver.h"

int main(int argc, char * argv[]) {
    std::string inFileName = argv[1];
    FILE * inFile = fopen(inFileName.c_str(), "rb");

    std::string outFileName = argv[1] + std::string(".usans");
    FILE * outFile = fopen(outFileName.c_str(), "wb");

    Task myTask;
    Point result;

    if (inFile == NULL || outFile == NULL) {
        std::cout << "Error: Files cannot opened!" << std::endl;
        return 0;
    }

    fread(&myTask, sizeof(myTask), 1, inFile);

    double time = omp_get_wtime();
    result = CalculateOptimum(&myTask);
    time = omp_get_wtime() - time;

    fwrite(&result, sizeof(result), 1, outFile);
    fwrite(&time, sizeof(time), 1, outFile);

    if (!result.err) {
        std::cout << result.x << " " << result.y << std::endl;
        std::cout << time << " seconds\n";
    }
    else { std::cout << "Calculated error!" << std::endl; }

    fclose(inFile);
    fclose(outFile);

    return 0;
}
