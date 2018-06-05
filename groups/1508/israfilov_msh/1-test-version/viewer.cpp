#include <iostream>
#include <fstream>

int main(int argc, char * argv[]) {
    double x, y, time;
    bool err;
    std::string strX, strY, strErr, strTime;

    if (argc < 3) {
        std::cout << "Error: Wrong amount of args" << std::endl;
    }

    std::string inFileName = argv[1];
    std::string outFileName = argv[2];

    FILE * inFile = fopen(inFileName.c_str(), "rb");
    std::ofstream outFile(outFileName.c_str());


    if (inFile == NULL || !outFile.is_open()) {
        std::cout << "Error: Files cannot opened!" << std::endl;
        return 0;
    }

    fread(&x, sizeof(x), 1, inFile);
    fread(&y, sizeof(y), 1, inFile);
    fread(&err, sizeof(err), 1, inFile);
    fread(&time, sizeof(time), 1, inFile);

    std::cout << x << std::endl << y << std::endl << err << std::endl << time << std::endl;

    strX = "x = " + std::to_string(x);
    strY = "y = " + std::to_string(y);
    strErr = "Calculation error: " ;
    strErr += ((err == 1) ? "true" : "false");
    strTime = "Calculation time: " + std::to_string(time);

    outFile << strX << "\n" << strY << "\n" << strErr << "\n" << strTime << std::endl;

    fclose(inFile);
    outFile.close();

    return 0;
}
