#ifndef STRONGINMETHOD_OMP_SOL_H
#define STRONGINMETHOD_OMP_SOL_H

#include <omp.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>


using std::vector;
using std::make_pair;
using std::pair;

typedef vector<pair<double, double>> vecP;

struct Task
{
    int funcNum;
    int maxOfIterations;
    double xl;
    double xr;
    double eps;
    int r;
};

struct Point
{
    double x;
    double y;
    bool err;
};

double Function(double, int);
int Characteristic(vecP&, double);
double GetM(vecP&, int);
double SetPoint(pair<double, double>, pair<double, double>, double);
bool Distance(vecP::iterator, double);
Point CalculateOptimum(Task*, int);

#endif //STRONGINMETHOD_OMP_SOL_H
