#include <cmath>
#include <cstdio>
#include <random>
#include <ctime>

using namespace std;
FILE *stream;

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void generator1(int kol, int *func, int *zn, double *a, double* b)
{
	//+ - 1; - - 2; * - 3; / - 4   :zn
	for (int i = 0; i < kol; i++)
	{
		func[i] = rand() % 12 + 1;
		zn[i] = rand() % 4 + 1;
		a[i] = fRand(0, 19);
		b[i] = fRand(a[i], 20);
	}
}

void generator2(int kol, int *func, int *zn, double *a, double* b)
{
	//+ - 1; - - 2; * - 3; / - 4   :zn
	for (int i = 0; i < kol; i++)
	{
		func[i] = rand() % 12 + 1;
		zn[i] = rand() % 4 + 1;
		a[i] = fRand(-10, 9);
		b[i] = fRand(a[i], 10);
	}
}

int main(int argc, char * argv[])
{
	srand(time(0));
	int n = 10;	
	const char* fout= "1";
	bool gen = true;
	if (argc > 1)
		n = atoi(argv[1]);	
	if (argc > 2)
		gen = atoi(argv[2]);
	if (argc > 3)
		fout = argv[3];
	int *func = new int[n];
	int *zn = new int[n];
	double *a = new double[n];
	double *b = new double[n];
	if(gen)
		generator1(n, func, zn, a, b);
	else
		generator2(n, func, zn, a, b);
	
	freopen_s(&stream, fout, "wb", stdout);
	fwrite(&n, sizeof(n), 1, stdout);
	fwrite(func, sizeof(*func), n, stdout);
	fwrite(zn, sizeof(*zn), n, stdout);
	fwrite(a, sizeof(*a), n, stdout);
	fwrite(b, sizeof(*b), n, stdout);
	fclose(stream);
	return 0;
}

