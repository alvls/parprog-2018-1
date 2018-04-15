// NEED OPENMP 4.0

#include <omp.h>
#include <vector>
#include <algorithm>

using namespace std;

// That is serial alg.
void hoaraSortOMP(double* &arr, int first, int last){
    int leftIndex = first,
        rightIndex = last;
    double tmp,
        pivot = arr[(first + last) / 2];

    do {
       while (arr[leftIndex] < pivot)
         leftIndex++;
       while (arr[rightIndex] > pivot)
         rightIndex--;

       if (leftIndex <= rightIndex)
       {
         if (leftIndex < rightIndex)
         {
           tmp = arr[leftIndex];
           arr[leftIndex] = arr[rightIndex];
           arr[rightIndex] = tmp;
         }
         leftIndex++;
         rightIndex--;
       }
    } while (leftIndex <= rightIndex);

    if (leftIndex < last)
       hoaraSortOMP(arr, leftIndex, last);
    if (first < rightIndex)
       hoaraSortOMP(arr, first, rightIndex);
}

int binSearch(double x, double* &vec, int N){

  int size = N / 2;
  int median = N / 2;

  while (true) {
      size = (size == 0) ? 1 : (size /= 2);

      if (vec[median] < x) {
        if (vec[median + 1] >= x)
          return median;
        else
          median += size;
      }
      else if (vec[median] > x) {
        if (vec[median + 1] <= x)
          return median;
        else
          median -= size;
      }
      else {
          while (median > 0 && vec[median] == x)
            median--;
          return median;
      }

      if (median == 0)
        return -1;
      else if (median == N)
        return N;
  }
}

double* vectorToDouble(vector<double>& vec){
  double* result = new double[vec.size()];

  for(int i = 0; i < vec.size(); ++i)
    result[i] = vec[i];

  return result;
}

vector<double> mergeDivideConquer(vector<double>& left,vector<double>& right, int threads) {
  vector<double> result;

  if ((left.size() + right.size()) <= 100) {
      result.resize(left.size() + right.size());
      merge(left.begin(), left.end(), right.begin(), right.end(), result.begin());

    return result;
  }

  int elementsThread = left.size() / threads;
  int otherElements = left.size() - threads * elementsThread;

  vector<vector<double>> lefts(threads);
  vector<vector<double>> rights(threads);

  for(int i =0; i < threads; ++i) {
      int k = i * elementsThread + ((i < otherElements) ? i : otherElements);
      lefts.at(i).resize(elementsThread + ((i < otherElements) ? 1 : 0));
      for(int j = 0; j < lefts.at(i).size(); ++j){
          lefts.at(i).at(j) = left.at(k);
          k++;
      }
  }

  vector<double> tmp(right.begin(), right.end());

  for(int i = 0; i < threads-1; ++i) {
      double* doubleAr = vectorToDouble(tmp);

      int bso = binSearch(lefts.at(i).at(lefts.at(i).size()-1), doubleAr, tmp.size());
      rights.at(i) = *(new vector<double>(tmp.begin(), tmp.begin() + bso + 1));
      tmp = *(new vector<double>(tmp.begin() + bso + 1, tmp.end()));

      delete[] doubleAr;
    }

  rights.at(threads - 1) = *(new vector<double>(tmp.begin(), tmp.end()));

  #pragma parallel for shared (lefts, rights)
  for(int i=0; i < threads; ++i) {
      vector<double> tmp(lefts.at(i).size() + rights.at(i).size());

      merge(lefts.at(i).begin(), lefts.at(i).end(), rights.at(i).begin(), rights.at(i).end(), tmp.begin());
      lefts.at(i) = tmp;
  }

  result.resize(left.size() + right.size());

  for(int i = 0; i < threads; ++i){
      int k = 0;
      for(int z = 0; z < i; ++z)
        k += lefts.at(z).size();
      for (int j = 0; j < lefts.at(i).size(); ++j, ++k)
        result.at(k) = lefts.at(i).at(j);
  }

  return result;
}

vector<double>& mainMerge(vector<vector<double>>& vecs, int threads) {
  double iterations = log2(threads);
  int i = 0;
  int dis = 1;

  while(i < iterations) {
  #pragma omp parallel for shared(vecs,i,dis)
      for(int j = 0; j < threads; j += (dis * 2)) {
          if((j + dis) < threads) {
            vecs.at(j) = mergeDivideConquer(vecs.at(j), vecs.at(j + dis),threads);
            }
      }

      dis *= 2;
      i++;
    }

  return vecs.at(0);
}

void IHoaraSortOMP(double* &numbs, int N, int threads) {
  omp_set_num_threads(threads);

  int elementsThread=N/threads;
  int otherElements=N-elementsThread*threads;

  vector<vector<double>> vecs(threads);

  #pragma omp parallel for shared(numbs)
  for (int i = 0; i < threads; ++i) {
      int leftIndex = elementsThread*i+((i < otherElements) ? i : otherElements);
      int rightIndex = leftIndex + ((i < otherElements) ? elementsThread : (elementsThread - 1));
      vector<double> ar(rightIndex - leftIndex + 1);

      hoaraSortOMP(numbs, leftIndex, rightIndex);

      for(int j = (leftIndex); j < (rightIndex + 1); ++j)
        ar[j - leftIndex] = numbs[j];

      vecs.at(i) = ar;
  }

  vector<double> mergeResult;
   if (threads > 1)
     {
      #pragma omp single
      mergeResult = mainMerge(vecs, threads);
     }
   else
     mergeResult = vecs.at(0);

   delete[] numbs;
   numbs = vectorToDouble(mergeResult);
}
