#ifndef STRONGINMETHOD_SOL_H
#define STRONGINMETHOD_SOL_H

#include <map>
#include <cmath>

using std::map;
using std::make_pair;

typedef map<double, double> mapP;

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
mapP::iterator Characteristic(mapP&, double);
double GetM(mapP&, int);
double SetPoint(mapP::iterator, mapP::iterator, double);
bool Distance(mapP::iterator, double);
Point CalculateOptimum(Task*);

#endif //STRONGINMETHOD_SOL_H
