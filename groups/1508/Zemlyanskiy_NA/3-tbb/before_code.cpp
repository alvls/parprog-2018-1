//9. Сортировка Шелла с четно-нечетным слиянием Бэтчера.
#include "tbb.h"
#include <iostream>
#include <omp.h>
#include <cstdio>
#include <string>

using namespace std;

void tbb_Shell_Sort(int *arr, int size, int threads);

int main(int argc, char* argv[]) {
    if(argc != 4) {
        cout<<"Can't run the programm"<<endl;
        cout << "Please enter the arguments" << endl;
        cout << "Like this: ./before_code [in_file_name.bin] [out_file_name.bin] [number_of_threads]"<<endl;
        exit(-1);
    }

    int length = 0;
    int threads = atoi(argv[3]);

    string start_in_name = "tests/input/";
    string start_out_name = "tests/output/";
    string end_in_name = argv[1];
    string end_out_name = argv[2];

    string in_file_name = start_in_name + end_in_name;
    string out_file_name = start_out_name + end_out_name;

    FILE* in_file = fopen(in_file_name.c_str(), "rb");
    FILE* out_file = fopen(out_file_name.c_str(), "wb");

    fread(&length, sizeof(length), 1, in_file);

    int *Arr_Shell = new int[length];

    fread(Arr_Shell,sizeof(*Arr_Shell), length, in_file);

    double time = omp_get_wtime();
    tbb_Shell_Sort(Arr_Shell, length, threads);
    time = omp_get_wtime() - time;

    fwrite(&time, sizeof(time), 1, out_file);
    fwrite(&length, sizeof(length), 1, out_file);
    fwrite(Arr_Shell,sizeof(*Arr_Shell),length,out_file);

    cout << "THE END" << endl;

    delete Arr_Shell;
    fclose(in_file);
    fclose(out_file);

    return 0;
}
