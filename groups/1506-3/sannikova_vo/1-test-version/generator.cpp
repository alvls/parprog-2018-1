//#define _CRT_SECURE_NO_WARNINGS
//#include <cstdio>
//#include <random>
//#include <ctime>
//#include <chrono>
//#include <iostream>
//using namespace std;
//
//int  n_tests[] = { 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
//int main(int argc, char * argv[])
//{
//	if (argc != 2 || atoi(argv[1]) < 1 || atoi(argv[1]) > 20)
//	{
//		cout << "Use 'generator [test number (1 - 20)]'" << endl;
//		return 1;
//	}
//	int n = n_tests[atoi(argv[1] - 1)]; //количество элементов в сгенерированном массиве
//	
//	// перенаправляем поток stdout в файл arr.in который стоит первым в командной строке
//	freopen(argv[1], "wb", stdout);
//	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
//	uniform_real_distribution <double> distribution(-1e4, 1e4);
//	
//	//fwrite
//	double tmp;	
//	fwrite(&tmp, sizeof(tmp), 1, stdout); //ввод времени прозапас 
//	fwrite(&n, sizeof(n), 1, stdout);
//	double * cur = new double[n];
//	vector <double> cur_vec(n);
//	
//	// генерируем массив/вектор 
//	for (int i = 0; i < n; i++){
//		// заполняем случайными числами из равномерного распределения массив
//		cur[i] = distribution(generator);
//		//cur[i] = tmp;
//
//		//cur_vec.push_back(tmp);
//		//fwrite(&cur_vec[i], sizeof(double), 1, stdout);
//	}
//	// записываем строку в бинарном виде в файл
//	fwrite(cur, sizeof(*cur), n, stdout);
//	// аналогично генерируем вторую матрицу
//
//	return 0;
//}
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <random> 
#include <ctime> 
#include <chrono>
#include <iostream>

using namespace std;

int n_tests[] = { 1, 2, 3, 5, 7, 8, 10, 100, 500, 1000, 5000, 10000, 10000, 500000, 100000, 1000000, 10000000, 25000000, 50000000, 100000000 };

int main(int argc, char * argv[])
{
	if ( atoi(argv[1]) < 1 || atoi(argv[1]) > 20 || argc != 2)
	{
		cout << "You input incorrect number. Try again. ONLY 1-20" << endl;
		return 1;
	}
	int n = n_tests[atoi(argv[1]) - 1]; //count of elements in vector/array

	string name = argv[1]; 
	string type = ".bin";
	name += type;
	freopen(name.c_str(), "wb", stdout);

	default_random_engine generator(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
	uniform_real_distribution <double> distribution(0, 1000);

	fwrite(&n, sizeof(double), 1, stdout); 
	fwrite(&n, sizeof(n), 1, stdout);

	double x;
	for (int i = 0; i < n; i++) {
		//arr[i] = distribution(generator);
		x = distribution(generator);
		fwrite(&x, sizeof(x), 1, stdout);
		//cout << (double)distribution(generator) << endl;
	}
	return 0;
}