// ��������� ������
#include <cstdio>
#include <random>
#include <chrono>
#include <vector>
#include <string>

using namespace std;

//25 ��������� ������� �����
int n_tests[] = { /*�1*/1, /*�2*/2, /*�3*/2, /*�4*/5, /*�5*/5, /*�6*/10, /*�7*/10, /*�8*/100, /*�9*/100, /*�10*/500, /*�11*/1000, /*�12*/2000, /*�13*/5000,
/*�14*/10000, /*�15*/25000, /*�16*/50000, /*�17*/100000, /*�18*/200000, /*�19*/500000, /*�20*/1000000, /*�21*/2000000, /*�22*/5000000, /*�23*/10000000, /*�24*/50000000, /*�25*/100000000 };

int main(int argc, char * argv[])
{
	// ������ ��������� ��������� ����� � seed ������ ���������� ������� � ������ �����
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	// ������ ����������� ������������� ��������� �������� ���� int � ��������� [-100000000, 100000000]
	uniform_int_distribution <int> distribution(-1e8, 1e8);
	// ������ �����
	int n;

	if (argc <= 1)
		return 0;

	// �������������� ����� stdout � ����
	freopen((".\\tests\\" + string(argv[1])).c_str(), "wb", stdout);
	// ���� �������� ����� ����� � ���������� ��������� ������, �� ���� ������ �� n_tests 
	//(������ ������ ��� ����� ���������� � �������)
	n = n_tests[atoi(argv[1]) - 1];
	//���������� ���������� ��������� ��� ��������� ����� ��� �������� Viewer'��
	fwrite(&n, sizeof(double), 1, stdout);
	// ���������� � �������� ���� ���������� ��������� �������
	fwrite(&n, sizeof(int), 1, stdout);
	// ������ ������ ��� ��������� �����
	vector<int> vec(n);
	// ����������
	for (size_t i = 0; i < n; ++i)
	{
		vec[i] = distribution(generator);
	}
	// ���������� ������ � �������� ���� � ����
	fwrite(vec.data(), sizeof(int), n, stdout);

	fclose(stdout);
}