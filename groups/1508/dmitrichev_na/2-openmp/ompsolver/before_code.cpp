#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <new>
#include "sol.cpp"
#include "../../../lab/src/solver/sol.cpp"

int main(int argc, char* argv[])
{
   if (argc != 4) {
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
   if(atoi(argv[3]) < 1) {
     cerr << argv[0] << " -> ERROR: number of threads has to be more than 0 '"<<argv[3]<<"'\n";
     exit(1);
   }

   int N = 0;
   double *numbers = NULL;
   double trash=0;
   int threads=atoi(argv[3]);

   fread(&trash, sizeof(trash), 1, fIn);
   fread(&N, sizeof(N), 1, fIn);
   numbers = new double[N];
   double* seNum=new double[N];
   fread(numbers, sizeof(*numbers), N, fIn);

   for(int i = 0; i < N; ++i){
       seNum[i]=numbers[i];
     }

   double time2 = omp_get_wtime();
   IHoaraSort(seNum, N);
   time2 = omp_get_wtime() - time2;
   cout<<endl<<static_cast<long long>(time2 * 1e7)<<endl;

   double time = omp_get_wtime();
   IHoaraSortOMP(numbers, N, threads);
   time = omp_get_wtime() - time;

   fwrite(&time, sizeof(time), 1, fOut);
   fwrite(&N, sizeof(N), 1, fOut);
   fwrite(numbers, sizeof(*numbers), N, fOut);


   cout<<endl<<static_cast<long long>(time * 1e7)<<endl;

   cout<<(time2/time)<<endl;

   cout<< argv[0]<<" -> OK\n";

   fclose(fIn);
   fclose(fOut);
   delete[] numbers;
   delete[] seNum;
   return 0;
}
