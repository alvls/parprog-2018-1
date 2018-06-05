#include <omp.h>
#include <iostream>
#include "solver.h"
//#include "omp_solver.h"
//#include "tbb_solver.h"

int main(int argc, char * argv[]) {
    if (argc > 1) {
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

#ifdef STRONGINMETHOD_SOL_H
        double time = omp_get_wtime();
        result = CalculateOptimum(&myTask);
        time = omp_get_wtime() - time;
#else
        int threads_number = 1;
        if (argc > 2)
            threads_number = atoi(argv[2]);

        double time = omp_get_wtime();
        result = CalculateOptimum(&myTask, threads_number);
        time = omp_get_wtime() - time;
#endif

        fwrite(&result, sizeof(result), 1, outFile);
        fwrite(&time, sizeof(time), 1, outFile);

        fclose(inFile);
        fclose(outFile);
    }

    return 0;
}
