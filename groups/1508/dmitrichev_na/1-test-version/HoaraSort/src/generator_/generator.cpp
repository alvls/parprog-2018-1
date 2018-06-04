#include <iostream>
#include <random>
#include <chrono>

double* genFunc(const int N){
  double* ar=new double[N];
  std::default_random_engine generator(time(0));
  for(int i = 0; i < N; ++i){
      std::uniform_real_distribution<double> distribution(-10000.0,10000.0);
      ar[i] = distribution(generator);
    }
  return ar;
}

using namespace std;

int n_tests[] = {0,1,2,3,5,10,10,55,100,100,555,1000,
                 1000,5555,10000,10000,55555,100000,100000,555555,1000000,1000000, 5555555,10000000};


int main(int argc, char* argv[]) {
  if (argc != 3) {
      cerr << argv[0] << " -> ERROR: not enough arguments\n";
      exit(1);
  }

  if (atoi(argv[1])>23 || atoi(argv[1])<0){
      cerr << argv[0] << " -> ERROR: first parameter has to be >= 0 and <=23\n";
      exit(1);
  }

  FILE* outFile = NULL;
  if ((outFile = fopen(argv[2],"wb"))==NULL){
      cerr << argv[0] << " -> ERROR: can not open '"<<argv[2]<<"'\n";
      exit(1);
  }

  int N = n_tests[atoi(argv[1])];
  double* ar = genFunc(N);
  double trash=0; // need to be canon

  fwrite(&trash,sizeof(trash),1,outFile);
  fwrite(&N,sizeof(N),1,outFile);
  fwrite(ar,sizeof(*ar),N,outFile);

  cout << argv[0] << " -> OK\n";

  delete[] ar;
  return 0;
}
