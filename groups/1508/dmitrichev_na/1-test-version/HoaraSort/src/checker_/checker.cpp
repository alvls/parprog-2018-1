#include <iostream>
#include "classResult.h"

int main (int argc, char* argv[])
{
   if (argc != 2) {
      cerr << argv[0] << " -> ERROR: not enough arguments\n";
      exit(1);
   }

   FILE *buo = NULL;
   if ((buo=fopen(argv[1], "rb"))==NULL){
       cerr << argv[0] << " -> ERROR: can not open '"<<argv[1]<<"'\n";
       exit(1);
   }

   int No;
   double res_time;

   fread(&res_time, sizeof (res_time), 1, buo);
   fread(&No, sizeof (No), 1, buo);

   if (No==0){
       checker_result.write_message ("AC. Zero size array.");
       checker_result.write_verdict (verdict::AC);
   }
   else {
     double curNum, prevNum;

     fread(&curNum, sizeof (curNum), 1, buo);
     prevNum=curNum;

     bool result = true;
     for (int i = 1; i < No; ++i) {
         fread(&curNum, sizeof (curNum), 1, buo);
         if (curNum<prevNum)
         {
           result=false;
           break;
         }
         prevNum=curNum;
     }

     if (result)
     {
       checker_result.write_message ("AC. Array is sorted.");
       checker_result.write_verdict (verdict::AC);
     }
     else
     {
       checker_result.write_message ("WA. Array isn't sorted.");
       checker_result.write_verdict (verdict::WA);
     }
   }
   checker_result.write_time (res_time * 1e7);

   cout << argv[0] << " -> OK\n";

   fclose(buo);
   return 0;
}
