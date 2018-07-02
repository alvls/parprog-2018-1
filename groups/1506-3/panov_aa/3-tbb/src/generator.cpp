#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "../include/my_matrix.h"
using namespace std;
int n_tests[] = { 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 40, 80, 100, 200, 300, 400, 500,
600, 700, 800, 900, 1000, 3000};
Matrix getRandMatrix(int n, default_random_engine &generator, uniform_real_distribution<double> &distribution)
{
    Matrix m1(n, n);
    for (int i = 0; i < n*n; i++)
    {
        m1.vv[i] = distribution(generator);
    }
    return m1;
}
Matrix getRandSparseMatrix(int n, default_random_engine &generator, uniform_real_distribution<double> &distribution)
{
    double sparsePersent = 0.25;//std::min(15.0/n, 1.0);
    Matrix m1(n, n);
    vector<int> index(n*n);
    iota(index.begin(), index.end(), 0);
    for (int i = 0; i < sparsePersent*n*n; i++)
    {
        uniform_int_distribution <int> d(0, index.size() - 1);
        int tmp_ind = d(generator);
        int ind = index[tmp_ind];
        swap(index[tmp_ind], index[index.size()-1]);
        index.pop_back();
        m1.vv[ind] = distribution(generator);
        if (index.size() == 0)
            return m1;
    }
    return m1;
}
int main(int argc, char * argv[])
{
	string outputFileMatrix;
	string outputFileAnswer;
    
    // ����� ������ ������
    // ���� �������� ����� ����� � ���������� ��������� ������, �� ���� ������ �� n_tests
    int n = 10;
    if (argc > 1)
    {
		outputFileMatrix = argv[1];
        if (argc > 2)
        {
			outputFileAnswer = argv[2];
			if (argc > 3)
			{
				n = atoi(argv[3]);
				if (n < 26)
					n = n_tests[n];
			}
        }
    }

    freopen((outputFileMatrix).c_str(), "wb", stdout);
    // ������ ��������� ��������� �����
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    // ������ ����������� ������������� ��������� �������� ���� double � ���������
    // [-10, 10]
    uniform_real_distribution <double> distribution(-1e1, 1e1);
  
    // ���������� � �������� ���� ����������� ������
    fwrite(&n, sizeof(n), 1, stdout);
    // ���������� ������ �������
    Matrix m1 = getRandSparseMatrix(n, generator, distribution);
    fwrite(m1.getP(), sizeof(m1.vv[0]), n*n, stdout);
    // ���������� ������ �������
    Matrix m2 = getRandSparseMatrix(n, generator, distribution);
    fwrite(m2.getP(), sizeof(m2.vv[0]), n*n, stdout);

    // ���������� �����
    Matrix ans = m1*m2;
    freopen((outputFileAnswer).c_str(), "wb", stdout);
    fwrite(&n, sizeof(n), 1, stdout);
    fwrite(ans.getP(), sizeof(Element), n*n, stdout);
    return 0;
}