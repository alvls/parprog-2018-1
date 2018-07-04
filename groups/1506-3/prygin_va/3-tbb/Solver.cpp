#include <tbb\task.h>

/*class TBBMonteCarlo : public tbb::task
{
	double *_functionValues;
	int _N;
	double _leftBorderX, _leftBorderY, _rightBorderX, _rightBorderY;


	double averageCalculation(double *functionValues, int N) {

		auto average = 0.f;
		auto valuesSum = 0.f;
		for (int i = 0; i < N; i++) {
			valuesSum += functionValues[i];
		}
		average = valuesSum / N;
		return average;
	}
public :
	TBBMonteCarlo(double *functionValues, double leftBorderX, double leftBorderY, double rightBorderX, double rightBorderY, int N) :
		_functionValues(functionValues), _leftBorderX(leftBorderX), _leftBorderY(leftBorderY), _rightBorderX(rightBorderX), _rightBorderY(rightBorderY), _N(N)	{	}

	double MonteCarlo(double *functionValues, double leftBorderX, double leftBorderY, double rightBorderX, double rightBorderY, int N)
	{
		
	}

	tbb::task* execute() {

		auto average = averageCalculation(functionValues, N);
		auto square = (rightBorderX - leftBorderX)*(rightBorderY - leftBorderY);
		auto result = average*square;

		return NULL;
	}
};

double MonteCarlo(double *functionValues, double leftBorderX, double leftBorderY, double rightBorderX, double rightBorderY, int N)
{
	TBBMonteCarlo& t = *new (tbb::task::allocate_root())
		TBBMonteCarlo(functionValues, leftBorderX, leftBorderY, rightBorderX, rightBorderY, N);
	tbb::task::spawn_root_and_wait(t);
	return 0;
}*/




