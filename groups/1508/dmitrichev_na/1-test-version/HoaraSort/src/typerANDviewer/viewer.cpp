#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <new>

using namespace std;

int main(int argc, char* argv[])
{
  if (argc != 3) {
      cout << argv[0] << " -> ERROR: not enough arguments\n";
      exit(1);
  }

  ofstream outFile;
  FILE* inFile=NULL;
  if ((inFile=fopen(argv[1],"rb"))==NULL){
      cerr << argv[0] << " -> ERROR: can not open '"<<argv[1]<<"'\n";
      exit(1);
  }
  outFile.open(argv[2]);
  if (outFile.fail()) {
      cout << argv[0] << " -> ERROR: can not open '"<<argv[2]<<"'\n";
      exit(1);
  }

  double curNum;
  int size=0;
  double time=0;

  fread(&time,sizeof(time),1,inFile);
  outFile<<time<<endl;
  fread(&size,sizeof(size),1,inFile);
  outFile<<size<<endl;
  for(int i=0;i<size;++i){
      fread(&curNum,sizeof(curNum),1,inFile);
      outFile<<curNum<<" ";
  }
  outFile<<endl;

  cout << argv[0] << " -> OK\n";

  outFile.close();
  fclose(inFile);
  return 0;
}
