#include "tbb_solver.h"

double Function(double x, int funcNum)
{
	double result;

	switch (funcNum)
	{
	case 0:
		result = cos(x)*(x / 4);
		break;
	case 1:
		result = sin(x)*(x / 4);
		break;
	case 2:
		result = sqrt(pow(x, 2));
		break;
	case 3:
		result = exp(x);
		break;
	case 4:
		result = x;
		break;
	case 5:
		result = pow(x, 3);
		break;
	case 6:
		result = 7.0*pow(x, 2) + 3.5*x - 1.4;
		break;
	case 7:
		result = sqrt(x) - 12.4;
		break;
	case 8:
		result = atan(x);
		break;
	case 9:
		result = 2.1*x / (pow(x, 2) + 1.2);
		break;
	case 10:
		result = 1 / (1 + pow(x, 2));
		break;
	case 11:
		result = 31 * pow(x, 4) + 7 * pow(x, 3) - 2 * pow(x, 2) + x;
		break;
	case 12:
		result = -sqrt((1 - x) / (1 + x));
		break;
	case 13:
		result = sqrt((1 - x) / (1 + x));
		break;
	case 14:
		result = (3.8*pow(x, 2) + 6.2*x + 2.7) / (2.3*x + 1.9);
		break;
	case 15:
		result = 7;
		break;
	case 16:
		result = sqrt((pow(x, 2) - 1)*(9 - pow(x, 2)));
		break;
	case 17:
		result = x + 1 / x;
		break;
	case 18:
		result = (1 / (1 + x)) - (2 / pow(x, 2)) + (1 / (1 - x));
		break;
	case 19:
		result = (x + 1)*(x - 2) / (x - 1)*(x + 2);
		break;
	default:
		result = NAN;
	}

	return result;
}

int Characteristic(vecP& p, double m)
{
	int leftBorder;
	double res, tmp;


	res = m * (p[1].first - p[0].first) + (pow(p[1].second - p[0].second, 2) /
		(m * (p[1].first - p[0].first))) - 2 * (p[1].second + p[0].second);
	leftBorder = 0;

	tbbCharacteristics tbbRes(p, res, leftBorder, m);

	parallel_reduce(blocked_range<int>(1, p.size() - 1), tbbRes);

	if (res < tbbRes.getRes()) {
		res = tbbRes.getRes();
		leftBorder = tbbRes.getBorder();
	}

	return leftBorder;
}

double GetM(vecP& p, int r)
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

double SetPoint(pair<double, double> pair1, pair<double, double> pair2, double m)
{
	return 0.5 * (pair1.first + pair2.first) - 0.5 * (pair2.second - pair1.second) / m;
}

bool Distance(vecP::iterator newPoint, double eps)
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

Point CalculateOptimum(Task *pTask, int threads_num = 1)
{
	task_scheduler_init init(threads_num);

	Point result = { 0, 0, false };
	vecP Points;
	double B = pTask->xr;
	double A = pTask->xl;
	double tmpX, tmpY, m;
	int oldLeftX, i;

	if (!isfinite(Function(A, pTask->funcNum)) || !isfinite(Function(B, pTask->funcNum))) {
		result.err = true;
		return result;
	}

	Points.emplace_back(make_pair(A, Function(A, pTask->funcNum)));
	Points.emplace_back(make_pair(B, Function(B, pTask->funcNum)));

	if (Points[0].second < Points[1].second)
	{
		result.y = Points[0].second;
		result.x = Points[0].first;
	}
	else
	{
		result.y = Points[1].second;
		result.x = Points[1].first;
	}

	m = GetM(Points, pTask->r);

	for (i = 2; i < pTask->maxOfIterations; ++i)
	{
		oldLeftX = Characteristic(Points, m);


		tmpX = SetPoint(Points[oldLeftX], Points[oldLeftX + 1], m);
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

		Points.insert(std::upper_bound(Points.begin(), Points.end(), make_pair(tmpX, tmpY)), make_pair(tmpX, tmpY));
		auto newX = std::find(Points.begin(), Points.end(), make_pair(tmpX, tmpY));

		if (Distance(newX, pTask->eps))
			break;

		m = GetM(Points, pTask->r);
	}

	return result;
}
