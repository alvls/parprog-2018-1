#include "Sole.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

int size_TBB = 0;

double vec_TBB(double * x, double * y) {
	double res = 0;
	for (int i = 0; i < size_TBB; i++)
		res += x[i] * y[i];
	return res;
}

void NonlinearConjugateGradient_TBB(Sole * S, int num) {
	tbb::task_scheduler_init init(num);
	size_TBB = S->N;//Задание размера

	//Выделение памяти
	double * x = new double[size_TBB];//Вектор приближений
	double * d = new double[size_TBB];//Вектор направления
	double * g = new double[size_TBB];//Градиент
	double s;//Скалярный шаг, величина смещения по заданному направлению
	double coef;//Коэффициент во 2 шаге
	double * s_prev = new double[size_TBB];//Произведение вектора направления и матрицы
	double * x_prev = new double[size_TBB];//Предыдущее приближение
	double * d_prev = new double[size_TBB];//Предыдущий вектор направления
	double * g_prev = new double[size_TBB];//Предыдущий градиент

	//Перед выполнением первой итерации x0 и d0 полагаются равными нулю
	// для вектора g0 устанавливается значение -b
	tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
	[=, &x_prev, &d_prev, &g_prev](const tbb::blocked_range<int>& r) {
		for (int i = r.begin(); i != r.end(); i++) {
			x_prev[i] = 0;
			d_prev[i] = 0;
			g_prev[i] = S->b[i] * (-1);
		}
	}
	);

	//Цикл по количеству итераций
	for (int i = 0; i < size_TBB; i++) {
		//1. Вычисление градиента
		tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
			[=, &g](const tbb::blocked_range<int>& r) {
			for (int j = r.begin(); j != r.end(); j++)
				g[j] = vec_TBB(S->A[j], x_prev) - S->b[j];
		}
		);

		//2. Вычисление вектора направления
		coef = vec_TBB(g, g) / vec_TBB(g_prev, g_prev);
		if (isnan(coef)) coef = 0;
		tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
			[=, &d](const tbb::blocked_range<int>& r) {
			for (int j = r.begin(); j != r.end(); j++)
				d[j] = coef * d_prev[j] - g[j];
		}
		);

		//3. Вычисление величины смещения по заданному направлению
		tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
			[=, &s_prev](const tbb::blocked_range<int>& r) {
			for (int j = r.begin(); j != r.end(); j++)
				s_prev[j] = vec_TBB(S->A[j], d);
		}
		);
		s = vec_TBB(d, g) / vec_TBB(s_prev, d);
		if (isnan(s)) s = 0;

		//4. Вычисление нового приближения
		tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
			[=, &x](const tbb::blocked_range<int>& r) {
			for (int j = r.begin(); j != r.end(); j++)
				x[j] = x_prev[j] - s * d[j];
		}
		);

		//Замена текущих на предыдущие
		tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
			[=, &g_prev, &d_prev, &x_prev](const tbb::blocked_range<int>& r) {
			for (int j = r.begin(); j != r.end(); j++) {
				g_prev[j] = g[j];
				d_prev[j] = d[j];
				x_prev[j] = x[j];
			}
		}
		);
	}

	//Сохранение результата
	tbb::parallel_for(tbb::blocked_range<int>(0, size_TBB, size_TBB / num),
		[=, &S](const tbb::blocked_range<int>& r) {
		for (int i = r.begin(); i != r.end(); i++)
			S->x[i] = x[i];
	}
	);

	//Освобождение памяти
	delete[] x;
	delete[] d;
	delete[] g;
	delete[] s_prev;
	delete[] x_prev;
	delete[] d_prev;
	delete[] g_prev;
}
