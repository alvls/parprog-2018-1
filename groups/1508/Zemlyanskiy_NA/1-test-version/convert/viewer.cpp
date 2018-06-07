//bin to txt
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>

using namespace std;

int main(int argc,char* argv[]) {
  string start_in_name = "tests/output/";
  string start_out_name = "convert/txt/";
  string end_in_name = argv[1];
  string end_out_name = argv[2];

  string in_file_name = start_in_name + end_in_name;
  string out_file_name = start_out_name + end_out_name;

  FILE* in_file = fopen(in_file_name.c_str(),"rb");
  ofstream out_file(out_file_name.c_str());

  if(argc != 3) {
    cout << "Can't start the programm" << endl;
    cout << "Please enter the arguments" << endl;
    cout << "Like this: ./viewer [file_name.bin] [file_name.txt]"<<endl;
    exit(-1);
  }

  if(in_file == NULL) {
    cout << "Can't open file" << endl;
    exit(-1);
  }

  int number = 0;
  int length = 0;
  double time = 0;

  fread(&time,sizeof(time),1,in_file);
  out_file<<time<<endl;
  fread(&length,sizeof(length),1,in_file);
  out_file<<length<<endl;
  for(int i=0;i<length;++i){
    fread(&number,sizeof(number),1,in_file);
    out_file<<number<<" ";
  }

  fclose(in_file);
  out_file.close();
  return 0;
}
