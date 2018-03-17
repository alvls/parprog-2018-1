#include <iostream>
#include <fstream>

struct Task
{
    int funcNum;
    int maxOfIterations;
    double xl;
    double xr;
    double eps;
    int r;
};

int main(int argc, char * argv[]) {
    Task inTask;

    if (argc < 3) {
        std::cout << "Error: Wrong amount of args" << std::endl;
    }

    std::string inFileName = argv[1];
    std::string outFileName = argv[2];

    std::ifstream inFile(inFileName.c_str());
    FILE * outFile = fopen(outFileName.c_str(), "wb");


    if (!inFile.is_open() || outFile == NULL) {
        std::cout << "Error: Files cannot opened!" << std::endl;
        return 0;
    }
    std::string inputString;
    std::string::size_type sz;

    std::getline(inFile, inputString);
    inTask.funcNum = std::stoi(inputString, &sz);

    std::getline(inFile, inputString);
    inTask.maxOfIterations = std::stoi(inputString, &sz);

    std::getline(inFile, inputString);
    inTask.xl = std::stod(inputString, &sz);

    std::getline(inFile, inputString);
    inTask.xr = std::stod(inputString, &sz);

    std::getline(inFile, inputString);
    inTask.eps = std::stod(inputString, &sz);

    std::getline(inFile, inputString);
    inTask.r = std::stoi(inputString, &sz);

    fwrite(&inTask, sizeof(inTask), 1, outFile);

    inFile.close();
    fclose(outFile);

    return 0;
}
