// NEED OPENMP 4.0

#include <omp.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

struct VECTOR{
  vector<double>* ar;
  int leftIndex=0;
  int rightIndex=0;
};

bool hoaraSortOMP(VECTOR& vec, int threads)
{
  if(vec.rightIndex==vec.leftIndex)
    return true;

  int leftI = vec.leftIndex,
      rightI=vec.rightIndex;

  double tmp,
      x = vec.ar->at((vec.rightIndex + vec.leftIndex) / 2);

  do {
     while (vec.ar->at(leftI) < x)
       leftI++;

     while (vec.ar->at(rightI) > x)
       rightI--;


     if (leftI <= rightI)
     {
       if (leftI < rightI)
       {
         swap(vec.ar->at(leftI),vec.ar->at(rightI));
       }

       leftI++;
       rightI--;
     }
  } while (leftI <= rightI);

  VECTOR left;
  VECTOR right;

  left.ar =vec.ar;
  right.ar=vec.ar;

  left.leftIndex=leftI;
  left.rightIndex=vec.rightIndex;

  right.leftIndex=vec.leftIndex;
  right.rightIndex=rightI;

  if (leftI < vec.rightIndex)
    hoaraSortOMP(left, threads);

  if (vec.leftIndex< rightI)
    hoaraSortOMP(right, threads);

   return true;
}

int binSearch(double& x, vector<double>& vec){

  int size=vec.size()/2;
  int median=vec.size()/2;

  while(1){
      size=(size==0)?1:(size/=2);

      if(vec.at(median)<x){
        if(vec.at(median+1)>=x)
          return median;
        else{

          median+=size;
          }
        }
      else if (vec.at(median)>x){
          if(vec.at(median+1)<=x)
            return median;
          else{
          median-=size;
            }
        }
      else {
          while(median>0 && vec.at(median)==x)
            median--;
          break;
        }
      if (median==0)
        return -1;
      else if (median == vec.size())
        return vec.size();
    }
  return median;
}

vector<double> simpleMerge(vector<double>& left, vector<double>& right){
  vector<double> result(left.size()+right.size());
  int i=0,
      j=0,
      k=0;

  while(1){
      if(i>=left.size()) {
        #pragma omp parallel for shared(result)
        for (int z = j; z < right.size(); ++z) {
          result.at(left.size()+z)=right.at(z);
        }
        break;
      }
      else if(j>=right.size()){
        #pragma omp parallel for shared(result)
        for (int z = i; z < left.size(); ++z){
          result.at(right.size()+z)=left.at(z);
        }
          break;
        } else {
          if(left.at(i) < right.at(j)) {
              result.at(k)=left.at(i);
              i++;
              k++;
            } else {
              result.at(k)=right.at(j);
              j++;
              k++;
            }
        }
    }
  return result;
}

vector<double> mergeDivideConquer(vector<double>& left,vector<double>& right, int threads){
  vector<double> result;
  if (left.size()<=500 || right.size()<=500){
    result.insert(result.end(),left.begin(),left.end());
    result.insert(result.end(),right.begin(),right.end());
    sort(result.begin(),result.end());
    return result;
    }

  int elementsThread = left.size()/threads;
  int otherElements = left.size() - threads*elementsThread;

  vector<vector<double>> lefts(threads);
  #pragma omp parallel for shared(lefts)
  for(int i =0; i < threads; ++i){
      int k= i * elementsThread + ((i<otherElements)?i:otherElements);
      lefts.at(i).resize(elementsThread+((i<otherElements)?1:0));
      for(int j = 0; j < lefts.at(i).size(); ++j){
          lefts.at(i).at(j)=left.at(k);
          k++;
        }
    }

  vector<vector<double>> rights(threads);

  int bso=binSearch(left.at(elementsThread),right);
  rights.at(0)=*(new vector<double>(right.begin(),right.begin()+bso+1));
  vector<double> tmp(right.begin()+bso+1,right.end());

  for(int i = 1; i < threads-1; ++i){
      bso=binSearch(left.at(elementsThread*(i+1)),tmp);
      rights.at(i)=*(new vector<double>(tmp.begin(),tmp.begin()+bso+1));
      tmp=*(new vector<double>(tmp.begin()+bso+1,tmp.end()));
    }
  rights.at(threads-1)=*(new vector<double>(tmp.begin(),tmp.end()));

  #pragma omp parallel for shared(lefts, rights)
  for( int i=0; i < threads; ++i){
      lefts.at(i)=simpleMerge(lefts.at(i),rights.at(i));
  }

  result.resize(left.size()+right.size());

  for ( int i = 0; i < lefts.at(0).size(); ++i)
    result.at(i)=lefts.at(0).at(i);

  #pragma omp parallel for shared (result)
  for(int i =1; i < threads; ++i){
      int k=0;
      for( int z = 0; z < i; ++z)
        k += lefts.at(z).size();
      for ( int j = 0; j < lefts.at(i).size(); ++j,++k)
        result.at(k) = lefts.at(i).at(j);
  }

  return result;
}

// MAKE std::vector from VECTOR
vector<double> makeSTDVector(VECTOR& vec) {
  vector<double> result(vec.rightIndex - vec.leftIndex+1);

  #pragma omp parallel for shared(result,vec)
  for (int i = vec.leftIndex; i < vec.rightIndex + 1; ++i){
    result.at(i-vec.leftIndex) = (vec.ar->at(i));
  }

  return result;
}

vector<double>& mainMerge(vector<vector<double>>& vecs, int threads){
  double iters = log2(threads);
  int it = (int)iters;
  int i = 0;
  int dis = 1;

  while(i < iters) {
  #pragma omp parallel for firstprivate(dis)
      for(int j = 0; j < threads; j += (dis * 2)) {
          if((j+dis) < threads)
            vecs.at(j) = mergeDivideConquer(vecs.at(j), vecs.at(j + dis),threads);
      }

      dis *= 2;
      i++;
      it = (it != 1) ? ((it + 1) / 2) : 1;
    }
  return vecs.at(0);
}

void IHoaraSortOMP(double* &numbs, int N, int threads) {
  omp_set_num_threads(threads);

  VECTOR vec;
  vec.leftIndex=0;
  vec.rightIndex=N-1;
// NEW vec.ar
  vec.ar = new vector<double>(N);

  #pragma omp parallel for shared(vec)
  for(int i = 0; i < N; ++i){
    vec.ar->at(i)=numbs[i];
  }
// NEW vectors
  VECTOR* vectors=new VECTOR[threads];

  int elementsThread=(vec.rightIndex+1)/threads;
  int otherElements=(vec.rightIndex+1)-elementsThread*threads;

// Init MASTER thread's struct
  vectors[0].ar=vec.ar;
  vectors[0].leftIndex=0;
  vectors[0].rightIndex=(0<otherElements)?(elementsThread):(elementsThread-1);

// Init other threads' structures
  #pragma omp parallel for shared(elementsThread,otherElements, vectors)
  for (int i=1;i<threads;++i){
      vectors[i].ar=vec.ar;
      //vectors[i].leftIndex=vectors[i-1].rightIndex+1;
      vectors[i].leftIndex=elementsThread*i+((i<otherElements)?i:otherElements);
      vectors[i].rightIndex=vectors[i].leftIndex+((i<otherElements)?elementsThread:(elementsThread-1));
  }

  vector<vector<double>> vecs(threads);
  #pragma omp parallel for shared(vecs, vectors,threads)
  for(int i=0; i < threads; ++i) {
// Sort number = %threads VECTORS
      hoaraSortOMP(vectors[i], threads);
// Make vector<double> for merging
      vecs.at(i)=makeSTDVector(vectors[i]);
  }

  vector<double> mergeResult;
  if (threads > 1)
    mergeResult = mainMerge(vecs, threads);
  else
    mergeResult = vecs.at(0);

  #pragma omp parallel for
  for (int i=0; i < N; ++i)
    numbs[i]=mergeResult.at(i);
// DELETE SECTION
// DELETE vec.ar
  delete vec.ar;
// DELETE vectors
  delete[] vectors;
}
