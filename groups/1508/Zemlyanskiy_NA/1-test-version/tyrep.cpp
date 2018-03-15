//txt to bin
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
  char* input = argv[1];
  FILE* file = fopen(input, "r");
  if (file == NULL) {
    printf("Can't open file\n");
    exit(-1);
  }
  int buffer;
  char str[5000];
  //ofstream ofs("input.bin"); //создать
  FILE *bin_file = fopen("array_in.bin", "wb");

  for (int i = 0; fgets(str, sizeof(str), file) != NULL; i++) {
  fread(&buffer, 1, 1, file);
  fwrite(&buffer, 1, 1, bin_file);
  }
  fclose(file);
  fclose(bin_file);

  return 0;
}
