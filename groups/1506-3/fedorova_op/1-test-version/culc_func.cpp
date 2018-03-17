#include <math.h>
#define PI 3.1412
#define E 2.718

double calculation_functions(double x, int _funcNum){
	double z = 0;
	switch (_funcNum)
	{
	case 0:
		z = sin(x) + sin(10 * x / 3); 
		break;
	case 1:
		z = (3 * x - 1.4)*sin(18 * x);
		break;
	case 2:
		z = -(x + sin(x))*pow(E, (-x*x));
		break;
	case 3:
		z = sin(x) + sin(10 * x / 3) + log(x) - 0.84*x + 3; 
		break;
	case 4:
		z = -sin(2 * PI * x)*pow(E, (-x));
		break;
	case 5:
		z = (x*x - 5 * x + 6) / (x*x + 1);
		break;
	case 6:
		z = -x + sin(3 * x) - 1; 
		break;
	case 7:
		z = 2 * pow((x - 3), 2) + pow(E, (x*x / 2));
		break;
	}
	return z;
}