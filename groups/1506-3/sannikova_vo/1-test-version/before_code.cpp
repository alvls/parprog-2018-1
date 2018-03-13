//#include <cstdio>
//#include <omp.h>
//#include <random>
//void qSort(double * arr, int size);
//int main(int argc, char * argv[])
//{
//	int num_threads = 1;
//	if (argc > 1)
//		num_threads = atoi(argv[1]);
//	int size;
//	double *arr;
//
//	freopen("arr.in", "rb", stdin);
//	freopen("arr.out", "wb", stdout);
//
//	fread(&size, sizeof(size), 1, stdin);
//
//	arr = new double[size];
//	fread(arr, sizeof(*arr), size, stdin);
//
//	//omp_set_num_threads(num_threads);
//	//double time = omp_get_wtime();
//	qSort(arr, size);
//
//	//time = omp_get_wtime() - time;
//	//fwrite(&time, sizeof(time), 1, stdout);
//	
//	fwrite(&size, sizeof(size), 1, stdout); // what
//	fwrite(arr, sizeof(*arr), size, stdout);
//	return 0;
//}
//#define main main_lumos_ 