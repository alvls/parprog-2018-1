#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <new>
#include <exception>
#include "sol.h"
//#include "stdafx.h"

using namespace std;

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
   double *numbersPar = NULL;
   double trash=0;
   int threads=atoi(argv[3]);

   fread(&trash, sizeof(trash), 1, fIn);
   fread(&N, sizeof(N), 1, fIn);

   numbersPar = new double[N];
   double* numbersSeq=new double[N];
   fread(numbersPar, sizeof(*numbersPar), N, fIn);

   for(int i = 0; i < N; ++i){
       numbersSeq[i]=numbersPar[i];
     }

   double seqTime = omp_get_wtime();
   hoaraSortTBB(numbersSeq,0, N-1);
   seqTime = omp_get_wtime() - seqTime;
   //cout<<endl<<static_cast<long long>(time2 * 1e7)<<endl;

   double parTime = omp_get_wtime();
   IHoaraSortTBB(numbersPar, N, threads);
   parTime = omp_get_wtime() - parTime;

   fwrite(&parTime, sizeof(parTime), 1, fOut);
   fwrite(&N, sizeof(N), 1, fOut);
   fwrite(numbersPar, sizeof(*numbersPar), N, fOut);

   cout<<(seqTime/parTime)<<endl;

   fclose(fIn);
   fclose(fOut);
   delete[] numbersPar;
   delete[] numbersSeq;
   return 0;
}
