//txt to bin
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

int main(int argc,char* argv[]) {
  string start_in_name = "convert/txt/";
  string start_out_name = "tests/input/";
  string end_in_name = argv[1];
  string end_out_name = argv[2];

  string in_file_name = start_in_name + end_in_name;
  string out_file_name = start_out_name + end_out_name;

  ifstream in_file;
  in_file.open(in_file_name.c_str(), ios_base::in);
  FILE* out_file = fopen(out_file_name.c_str(),"wb");

  if(argc != 3) {
    cout << "Can't start the programm" << endl;
    cout << "Please enter the arguments" << endl;
    cout << "Like this: ./tyrep [file_name.txt] [file_name.bin]"<<endl;
    exit(-1);
  }

  if(in_file.fail()) {
    cout << "Can't open file" << endl;
    exit(-1);
  }

  int length = 0;
  int number = 0;

  //double trash = 0;

  // in_file >> trash; // need it
  // fwrite(&trash, sizeof(trash), 1, out_file);

  in_file >> length;
  fwrite(&length,sizeof(length),1,out_file);

  for(int i = 0; i < length; ++i) {
    in_file >> number;
    fwrite(&number,sizeof(number),1,out_file);
  }
  in_file.close();
  fclose(out_file);
  return 0;
}
