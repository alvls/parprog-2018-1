/* Последовательная реализация алгоритма глобального поиска(АГП)
 * Корректность последовательного АГП проверена вручную,
 * путем сравнения результатов программы и графиков функций*/

#include <map>
#include <math.h>
#include "solver.h"

double Function(double x, int funcNum)
{
    double result;

    switch (funcNum)
    {
        case 0:
            result = cos(x)*(x/4);
            break;
        case 1:
            result = sin(x)*(x/4);
            break;
        case 2:
            result = sqrt(pow(x,2));
            break;
        case 3:
            result = exp(x);
            break;
        case 4:
            result = x;
            break;
        case 5:
            result = pow(x,3);
            break;
        case 6:
            result = 7.0*pow(x,2)+3.5*x-1.4;
            break;
        case 7:
            result = sqrt(x)-12.4;
            break;
        case 8:
            result = atan(x);
            break;
        case 9:
            result = 2.1*x/(pow(x,2)+1.2);
            break;
        case 10:
            result = 1/(1+pow(x,2));
            break;
        case 11:
            result = 31*pow(x, 4)+7*pow(x,3)-2*pow(x,2)+x;
            break;
        case 12:
            result = -sqrt((1-x)/(1+x));
            break;
        case 13:
            result = sqrt((1-x)/(1+x));
            break;
        case 14:
            result = (3.8*pow(x,2)+6.2*x+2.7)/(2.3*x+1.9);
            break;
        case 15:
            result = 7;
            break;
        case 16:
            result = sqrt((pow(x,2)-1)*(9-pow(x,2)));
            break;
        case 17:
            result = x+1/x;
            break;
        case 18:
            result = (1/(1+x))-(2/pow(x, 2))+(1/(1-x));
            break;
        case 19:
            result = (x+1)*(x-2)/(x-1)*(x+2);
            break;
        default:
            result = NAN;
    }

    return result;
}

mapP::iterator Characteristic(mapP& p, double m)
{
    mapP::iterator interval;
    double res, tmp;

    for (auto itPL = p.begin(), itPR = ++p.begin(); itPR != p.end(); ++itPL, ++itPR)
    {
        if (itPL == p.begin())
        {
            res = m * (itPR->first - itPL->first) + (pow(itPR->second - itPL->second, 2) /
                    (m * (itPR->first - itPL->first))) - 2 * (itPR->second + itPL->second);
            interval = itPL;
        }
        else
        {
            tmp = m * (itPR->first - itPL->first) + (pow(itPR->second - itPL->second, 2) /
                    (m * (itPR->first - itPL->first))) - 2 * (itPR->second + itPL->second);
            if (res < tmp)
            {
                res = tmp;
                interval = itPL;
            }
        }
    }

    return interval;
}

double GetM(mapP& p, int r)
{
    double result = 0, tmp;

    for (auto itPL = p.begin(), itPR = ++p.begin(); itPR != p.end(); ++itPL, ++itPR)
    {
        if (itPL == p.begin())
        {
            result = fabs(itPR->second - itPL->second) / (itPR->first - itPL->first);
        }
        else
        {
            tmp = fabs(itPR->second - itPL->second) / (itPR->first - itPL->first);
            if (result < tmp)
            {
                result = tmp;
            }
        }
    }

    return (result != 0) ? r*result : 1;
}

double SetPoint(mapP::iterator pair1, mapP::iterator pair2, double m)
{
    return 0.5 * (pair1->first + pair2->first) - 0.5 * (pair2->second - pair1->second) / m;
}

bool Distance(mapP::iterator newPoint, double eps)
{
    bool result = false;
    auto oldRightX = newPoint;
    auto oldLeftX = newPoint;
    ++oldRightX;
    --oldLeftX;

    if (fabs(newPoint->first - oldLeftX->first) < eps)
    {
        result = true;
    }
    else if (fabs(oldRightX->first - newPoint->first) < eps)
    {
        result = true;
    }

    return result;
}

Point CalculateOptimum(Task *pTask)
{
    Point result = {0, 0, false};
    mapP Points;
    double B = pTask->xr;
    double A = pTask->xl;
    double tmpX, tmpY, m;

    if (!isfinite(Function(A, pTask->funcNum)) || !isfinite(Function(B, pTask->funcNum))) {
        result.err = true;
        return result;
    }

    Points.insert(make_pair(A, Function(A, pTask->funcNum)));
    Points.insert(make_pair(B, Function(B, pTask->funcNum)));

    result.y = Points.begin()->second;
    result.x = Points.begin()->first;

    m = GetM(Points, pTask->r);

    for (int i = 2; i < pTask->maxOfIterations; ++i)
    {
        auto oldLeftX = Characteristic(Points, m);
        auto oldRightX = oldLeftX;
        ++oldRightX;

        tmpX = SetPoint(oldLeftX, oldRightX, m);
        tmpY = Function(tmpX, pTask->funcNum);

        if (!isfinite(tmpY)) {
            result.err = true;
            break;
        }

        if (tmpY < result.y)
        {
            result.y = tmpY;
            result.x = tmpX;
        }

        Points.insert(make_pair(tmpX, tmpY));
        auto newX = Points.find(tmpX);

        if (Distance(newX, pTask->eps))
            break;

        m = GetM(Points, pTask->r);
    }

    return result;
}
