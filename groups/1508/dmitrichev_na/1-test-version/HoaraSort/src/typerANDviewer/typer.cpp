#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <new>

using namespace std;

int main(int argc, char* argv[])
{
  if (argc != 3) {
      cerr << argv[0] << " -> ERROR: not enough arguments\n";
      exit(1);
  }

  ifstream inFile;
  FILE* outFile=NULL;
  if((outFile=fopen(argv[2],"wb"))==NULL) {
      cerr << argv[0] << " -> ERROR: can not open '"<<argv[2]<<"'\n";
      exit(1);
  }
  inFile.open(argv[1]);
  if (inFile.fail()) {
      cerr << argv[0] << " -> ERROR: can not open '"<<argv[1]<<"'\n";
      exit(1);
  }

  double curNum;
  double trash=0;
  inFile >> trash; // need it
  fwrite(&trash, sizeof(trash), 1, outFile);

  int size=0;
  inFile>>size;
  fwrite(&size,sizeof(curNum),1,outFile);
  for(int i=0;i<size;++i){
      inFile>>curNum;
      fwrite(&curNum,sizeof(curNum),1,outFile);
  }

  cout << argv[0] << " -> OK\n";

  inFile.close();
  fclose(outFile);
  return 0;
}
