#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <random>
#include <cstdlib>
#include <ctime>
#include <ctime>
#include <chrono>
#include<string>
#include <sstream>
#include <math.h>
#include <iostream>
#include <conio.h>
#include <utility>
#include <vector>

typedef std::pair<float, float> point;

double randomX(double min, double max)
{
	std::uniform_real_distribution<double>distribution(min, max);
	std::random_device rd;
	std::mt19937 generator(rd());
	return distribution(generator);
}

double randomY(double min, double max)
{
	std::uniform_real_distribution<double>distribution(min, max);
	std::random_device rd;
	std::mt19937 generator(rd());
	return distribution(generator);
}

double funcToCalculate(double x, double y) {
	return pow(x, 2) + pow(y, 2);
}

point CalculateRandomPoint(float leftBorderX, float leftBorderY, float rightBorderX, float rightBorderY)
{
	return std::make_pair(randomX(leftBorderX, rightBorderX), randomY(leftBorderY, rightBorderY));
}

void printPoint(point pointToPrint) {
	std::cout << "x = " << pointToPrint.first << " y = " << pointToPrint.second<<"\n";
}

/*int main(int argc, char * argv[])
{
	std::uniform_real_distribution<double>distribution(-1, 10);
	std::random_device rd;
	std::mt19937 generator(rd());

	double x1 = distribution(generator);
	double x2 = distribution(generator);
	if (x1 > x2) std::swap(x1, x2);

	double y1 = distribution(generator);
	double y2 = distribution(generator);
	if (y1 > y2) std::swap(y1, y2);

	int testCount = 1;
	int n = 100;
	if (argv[1])
		testCount = atoi(argv[1]);
	if (argv[2])
		n = atoi(argv[2]);
	 
	for (int i = 0; i < testCount; i++) {

		double x1 = distribution(generator);
		double x2 = distribution(generator);
		if (x1 > x2) std::swap(x1, x2);

		double y1 = distribution(generator);
		double y2 = distribution(generator);
		if (y1 > y2) std::swap(y1, y2);

		char index[10];

		freopen(_itoa(i, index, 10), "wb", stdout);
		fwrite(&n, sizeof(n), 1, stdout);
		fwrite(&x1, sizeof(x1), 1, stdout);
		fwrite(&x2, sizeof(x2), 1, stdout);
		fwrite(&y1, sizeof(y1), 1, stdout);
		fwrite(&y2, sizeof(y2), 1, stdout);

		double *functionValues = new double[n];

		for (int i = 0; i < n; i++)
		{
			auto newPoint = CalculateRandomPoint(x1, y1, x2, y2);
			auto funcToCalc = [](point p) -> double{
				//return pow(newPoint.first, 2) + pow(newPoint.second, 2);
				return (p.first + p.second );

			};
			auto funcValue = funcToCalc(newPoint);

			fwrite(&funcValue, sizeof(funcValue), 1, stdout);
		}
		
		fclose(stdout);
	}
	return 0;
}*/