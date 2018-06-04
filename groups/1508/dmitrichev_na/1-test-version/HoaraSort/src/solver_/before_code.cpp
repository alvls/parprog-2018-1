#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <new>
#include "sol.cpp"

using namespace std;

int main(int argc, char* argv[])
{
   if (argc != 3) {
      cerr << argv[0] << " -> ERROR: not enough arguments\n";
      exit(1);
   }
   FILE *fIn = NULL,
        *fOut = NULL;

   if ((fIn = fopen(argv[1], "rb")) == NULL) {
     cerr << argv[0] << " -> ERROR: can not open '"<<argv[1]<<"'\n";
     exit(1);
   }
   if ((fOut = fopen(argv[2], "wb")) == NULL) {
     cerr << argv[0] << " -> ERROR: can not open '"<<argv[2]<<"'\n";
     exit(1);
   }

   int N = 0;
   double *numbers = NULL;
   double trash=0;

   fread(&trash, sizeof(trash), 1, fIn);
   fread(&N, sizeof(N), 1, fIn);
   numbers = new double[N];
   fread(numbers, sizeof(*numbers), N, fIn);

   double time = omp_get_wtime();
   IHoaraSort(numbers, N); // the seq. hoara sort
   time = omp_get_wtime() - time;

   fwrite(&time, sizeof(time), 1, fOut);
   fwrite(&N, sizeof(N), 1, fOut);
   fwrite(numbers, sizeof(*numbers), N, fOut);

   cout<< argv[0]<<" -> OK\n";

   fclose(fIn);
   fclose(fOut);
   delete[] numbers;
   return 0;
}
