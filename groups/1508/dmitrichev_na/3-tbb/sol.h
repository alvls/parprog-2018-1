#pragma once

#include <vector>
#include <algorithm>
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/tbb.h"


void hoaraSortTBB(double* &arr, int first, int last){
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
		hoaraSortTBB(arr, leftIndex, last);
	if (first < rightIndex)
		hoaraSortTBB(arr, first, rightIndex);
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

std::vector<double> mergeSorted(std::vector<double>& left, std::vector<double>& right) {
	std::vector<double> result(left.size() + right.size());
	merge(left.begin(), left.end(), right.begin(), right.end(), result.begin());
	return result;
}

double* vectorToDouble(std::vector<double>& vec){
	double* result = new double[vec.size()];

	for(int i = 0; i < vec.size(); ++i)
	result[i] = vec[i];

	return result;
}

std::vector<double> mergeDivideConquer(std::vector<double>& left, std::vector<double>& right, int threads) {
	if ((left.size() + right.size()) <= 1000) {
		return mergeSorted(left, right);
	}
	int tmpThreads = (int)log2((int)(log10(left.size() + right.size())));
	int localThreads = (tmpThreads !=0)?((tmpThreads < threads)? tmpThreads :threads):1;

	int elementsThread = left.size() / localThreads;
	int otherElements = left.size() - localThreads * elementsThread;

	std::vector<std::vector<double>> lefts(localThreads);
	std::vector<std::vector<double>> rights(localThreads);

	tbb::parallel_for(size_t(0), size_t(localThreads), [&](size_t i) {
	//for(int i =0; i < localThreads; ++i) {
		int k = i * elementsThread + ((i < otherElements) ? i : otherElements);
		lefts.at(i).resize(elementsThread + ((i < otherElements) ? 1 : 0));
		for(int j = 0; j < lefts.at(i).size(); ++j){
			lefts.at(i).at(j) = left.at(k);
			k++;
		}
	});

	std::vector<double> tmp(right.begin(), right.end());

	for(int i = 0; i < localThreads - 1; ++i) {
		double* doubleAr = vectorToDouble(tmp);

		int bso = binSearch(lefts.at(i).at(lefts.at(i).size()-1), doubleAr, tmp.size());
		rights.at(i) = *(new std::vector<double>(tmp.begin(), tmp.begin() + bso + 1));
		tmp = *(new std::vector<double>(tmp.begin() + bso + 1, tmp.end()));

		delete[] doubleAr;
	}

	rights.at(localThreads - 1) = *(new std::vector<double>(tmp.begin(), tmp.end()));

	tbb::task_scheduler_init init(tbb::task_scheduler_init::deferred);

	init.initialize(localThreads);
	tbb::parallel_for(size_t(0), size_t(localThreads), [&lefts, &rights](size_t i) {
		lefts.at(i) = mergeSorted(lefts.at(i), rights.at(i));
	});
	init.terminate();

	std::vector<double> result(left.size() + right.size());

	init.initialize(localThreads);
	tbb::parallel_for(size_t(0),size_t(localThreads),[&](size_t i){
		int k = 0;
		for (int z = 0; z < i; ++z)
			k += lefts.at(z).size();
		for (int j = 0; j < lefts.at(i).size(); ++j, ++k)
			result.at(k) = lefts.at(i).at(j);
	});
	init.terminate();

	return result;
}

std::vector<double>& mainMerge(tbb::task_scheduler_init& tbbTSI, std::vector<std::vector<double>>& vecs, int threads) {
	double iterations = log2(threads);
	int i = 0;
	int dis = 1;

	while(i < iterations) {
		int curIterations = (int)(threads / (dis * 2));

		tbbTSI.initialize(threads);

		tbb::parallel_for(size_t(0), size_t(curIterations), [&](size_t j) {
			int leftVectorIndex = j * dis * 2;
			if ((leftVectorIndex + dis) < threads) {
				//vecs[leftVectorIndex] = mergeSorted(vecs[leftVectorIndex], vecs[leftVectorIndex+dis]);
				vecs[leftVectorIndex] = mergeDivideConquer(vecs[leftVectorIndex], vecs[leftVectorIndex + dis], threads);
			}
		});

		tbbTSI.terminate();
     
		dis *= 2;
		i++;
	}

	return vecs.at(0);
}

std::vector<std::vector<double>> sortThread(tbb::task_scheduler_init& tbbTSI, double* &numbs, int N, int threads) {
	int elementsThread = N / threads;
	int otherElements = N - elementsThread * threads;

	std::vector<std::vector<double>> resultVectors(threads);

	tbbTSI.initialize(threads);

	tbb::parallel_for(size_t(0), size_t(threads),[&](size_t i) {
		int leftIndex = elementsThread * i + ((i < otherElements) ? i : otherElements);
		int rightIndex = leftIndex + ((i < otherElements) ? elementsThread : (elementsThread - 1));

		resultVectors.at(i) = std::vector<double>(rightIndex - leftIndex + 1);
		hoaraSortTBB(numbs, leftIndex, rightIndex);

		for (int j = leftIndex; j < (rightIndex + 1); ++j)
			resultVectors[i].at(j-leftIndex) = numbs[j];
	});

	tbbTSI.terminate();

	return resultVectors;
}

void IHoaraSortTBB(double* &numbs, int N, int threads) {
	tbb::task_scheduler_init init(tbb::task_scheduler_init::deferred);

	std::vector<std::vector<double>> vecs = sortThread(init, numbs, N, threads);

	std::vector<double> mergeResult;

	if (threads > 1)
		mergeResult = mainMerge(init, vecs, threads);
	else
		mergeResult = vecs.at(0);
   
	delete[] numbs;
	numbs = vectorToDouble(mergeResult);
}
