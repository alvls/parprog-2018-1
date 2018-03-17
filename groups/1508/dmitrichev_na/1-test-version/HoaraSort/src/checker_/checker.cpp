#include <iostream>
#include "classResult.h"

int main (int argc, char* argv[])
{
   if (argc != 3) {
      std::cout << argv[0] << " -> ERROR: not enough arguments\n";
      exit(1);
   }

   FILE *buo = NULL,
        *bua = NULL;
   if ((buo=fopen(argv[1], "rb"))==NULL){
       cerr << argv[0] << " -> ERROR: can not open '"<<argv[1]<<"'\n";
       exit(1);
   }
   if ((bua=fopen(argv[2], "rb"))==NULL){
       cerr << argv[0] << " -> ERROR: can not open '"<<argv[2]<<"'\n";
       exit(1);
   }

   int N;
   double res_time;

   fread(&res_time, sizeof (res_time), 1, bua);
   fread(&res_time, sizeof (res_time), 1, buo);
   fread(&N, sizeof (N), 1, buo);
   double *ans = new double[N],
          *res = new double[N];
   fread(res, sizeof (*res), N, buo);
   fread(&N, sizeof (N), 1, bua);
   fread(ans, sizeof (*ans), N, bua);

   bool result = true;
   for (int i = 0; i < N; ++i)
     if (ans[i]!=res[i])
       {
         result=false;
         break;
       }

   if (result)
   {
     checker_result.write_message ("AC. Numbers are equal.");
     checker_result.write_verdict (verdict::AC);
   }
   else
   {
     checker_result.write_message ("WA. Output is not correct.");
     checker_result.write_verdict (verdict::WA);
   }

   checker_result.write_time (res_time * 1e7);

   cout << argv[0] << " -> OK\n";

   fclose(bua);
   fclose(buo);
   return 0;
}
