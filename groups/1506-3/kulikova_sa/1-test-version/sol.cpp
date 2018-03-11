#include <omp.h>
#include "Sole.h"

double vec(double * x, double * y, int size) {
	double res = 0;
	for (int i = 0; i < size; i++) {
		res += x[i] * y[i];
	}
	return res;
}

void NonlinearConjugateGradient(Sole * S) {
	//Размерность системы должно быть положительной, т.е N > 0

	//Матрица А должна быть симетричной, т.е А=Ат

	//Матрица А должна быть положительно определена, т.е xт*А*x > 0

	double * x = new double[S->N];//Вектор приближений
	double * d = new double[S->N];//Вектор направления
	double * g = new double[S->N];//Градиент
	double s;//Скалярный шаг, величина смещения по заданному направлению
	double * s_prev = new double[S->N];//Произведение вектора направление и матрицы
	double * x_prev = new double[S->N];//Предыдущее приближение
	double * d_prev = new double[S->N];//Предыдущий вектор направления
	double * g_prev = new double[S->N];//Предыдущий градиент
 
	//Перед выполнением первой итерации x0 и d0 полагаются равными нулю, а для вектора g0 устанавливается значение -b
	for (int i = 0; i < S->N; i++) {
		x_prev[i] = 0;
		d_prev[i] = 0;
		g_prev[i] = S->b[i] * (-1);
	}

	//Цикл по количеству итераций
	for (int i = 0; i < S->N; i++) {
		//1. Вычисление градиента
		for (int j = 0; j < S->N; j++)
			g[j] = vec(S->A[j], x_prev, S->N) - S->b[j];

		//2. Вычисление вектора направления
		for (int j = 0; j < S->N; j++)
			d[j] = vec(g, g, S->N) / vec(g_prev, g_prev, S->N) * d_prev[j] - g[j];

		//3. Вычисление величины смещения по заданному направлению
		for (int j = 0; j < S->N; j++)
			s_prev[j] = vec(S->A[j], d, S->N);
		s = vec(d, g, S->N) / vec(s_prev, d, S->N);

		//4. Вычисление нового приближения
		for (int j = 0; j < S->N; j++)
			x[j] = x_prev[j] - s * d[j];

		//Замена текущих на предыдущие
		for (int j = 0; j < S->N; j++) {
			g_prev[j] = g[j];
			d_prev[j] = d[j];
			x_prev[j] = x[j];
		}
	}

	//Сохранение результата
	for (int i = 0; i < S->N; i++)
		S->x[i] = x[i];
}
