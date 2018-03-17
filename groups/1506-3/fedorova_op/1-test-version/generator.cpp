
#include <random>
#include <chrono>
using namespace std;

double masEps[3] = { 0.0001, 0.001, 0.01 };
double masA[8] = {2.7, 0, -10, 2.7, 0, -5, 0, -3};
double masB[8] = {7.5, 1.2, 10, 7.5, 4, 5, 6.5, 3};

int main(int argc, char* argv[])
{
	 freopen("tests/1", "wb", stdout);
	 default_random_engine generation(chrono::system_clock::now().time_since_epoch().count());
	 uniform_int_distribution <int> distribution4(0,7);
	double parameter_r, epsilon, a, b; // параметр>1, останов по точности , интервал
	int funcNum = distribution4(generation); // какая из функций из исходника
	

	uniform_real_distribution <double> distribution1(masA[funcNum] *1.5-0.5, masA[funcNum]); 
	a = distribution1(generation);
	uniform_real_distribution <double> distribution2(masB[funcNum], masB[funcNum] *1.5);
	b = distribution2(generation);

	int k = rand() % 3;
	epsilon = masEps[k];
	
	uniform_real_distribution <double> distribution3(1.5, 3); 
	parameter_r = distribution3(generation);

	if (argc > 1)
	{
		funcNum = atoi(argv[1]);
		a = atoi(argv[2]);
		b = atoi(argv[3]);
		epsilon = atoi(argv[4]);
		parameter_r = atoi(argv[5]);
	}

	fwrite(&funcNum, sizeof(funcNum), 1, stdout);
	fwrite(&a, sizeof(a), 1, stdout);
	fwrite(&b, sizeof(b), 1, stdout);
	fwrite(&epsilon, sizeof(epsilon), 1, stdout);
	fwrite(&parameter_r, sizeof(parameter_r), 1, stdout);

	return 0;
}