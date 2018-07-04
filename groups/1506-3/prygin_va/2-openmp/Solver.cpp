#include <omp.h>

double averageCalculation(double *functionValues, int N) {
	
	auto average = 0.f;
	auto valuesSum = 0.f;
#pragma omp  for default(shared)
	for (int i = 0; i < N; i++) {
		valuesSum += functionValues[i];
	}
	average = valuesSum / N;
	return average;
}

double MonteCarlo(double *functionValues, double leftBorderX, double leftBorderY, double rightBorderX, double rightBorderY,  int N)
{
	auto average = averageCalculation(functionValues, N);
	auto square = (rightBorderX - leftBorderX)*(rightBorderY - leftBorderY);
	auto result = average*square;	
	return result;
}

