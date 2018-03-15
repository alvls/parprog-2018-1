// ��������� �������� ������������ �������
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

// ������������ ��� �������������� � ����������� ��������
////////////////////////////////////////////////////////////////////////////////////////////
/*
// Checker ����� ������������� ��� ��� ��� ��������:
AC = Accepted = ������� ����� ���������� ��������� �� ������ �����
WA = Wrong Answer = ������� ����� ������������ ��������� �� ������ �����
PE = Presentation Error = ������ ������� �������� ������
// ��������� �������� checker �� ����� �������������
NO = No verdict = ������� �����������
CE = Compilation Error = ������ ����������
ML = Memory Limit Exceeded = ��������� ����������� �� ������
TL = Time Limit Exceeded = ��������� ����������� �� ������� ������
RE = Runtime Error = ������ ������� ���������� ���������
IL = Idle Limit Exceeded = ��������� ����� ������� (�����������) ���������
DE = Deadly Error = ������ ����������� �������
*/

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };
class result
{
private:
	FILE * bur;
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
	result(bool read = false)
	{
		if (read) bur = fopen((".\\tests\\" + string("result.txt")).c_str(), "r"); 
		else bur = fopen((".\\tests\\" + string("result.txt")).c_str(), "a");
	}
	~result() 
	{ 
		fprintf(bur, "\n");
		fclose(bur); 
	}
	void write_type(ext_cls t)
	{
		/*fwrite(&t, sizeof(t), 1, bur);*/
		switch (t)
		{
		case NO:
			fprintf(bur, "%s", "NO");
			break;
		case VERDICT:
			fprintf(bur, "%s", "VERDICT");
			break;
		case MESSAGE:
			fprintf(bur, "%s", "MESSAGE");
			break;
		case TIME:
			fprintf(bur, "%s", "TIME");
			break;
		case MEMORY:
			fprintf(bur, "%s", "MEMORY");
			break;
		}
	}
	// �������� ����������� �������, ��� ������� �������� ���� �� ��������� verdict
	void write_verdict(verdict v)
	{
		write_type(ext_cls::VERDICT);
		/*fwrite(&v, sizeof(v), 1, bur);*/
		fprintf(bur, " ");
		switch (v)
		{
		case AC:
			fprintf(bur, "%s", "AC");
			break;
		case WA:
			fprintf(bur, "%s", "WA");
			break;
		case PE:
			fprintf(bur, "%s", "PE");
			break;
		}
	}
	// �������� ��������� �� checker'a ������������.
	// ��������, ��� ������� ������, ��� ��������.
	// ������������ ������ ��������� ����� � ����� ����������
	void write_message(string str)
	{
		write_type(ext_cls::MESSAGE);
		int l = str.size();
		/*fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);*/
		//fprintf(bur, "%i", l);
		fprintf(bur, "%s", (" " + str).c_str());
	}
	// �������� ����������� ������� ����� ������ ��������� ���������,
	// ����������� � ������� before_code
	// x ����� ����������� 100 �� = 10 ^ (-7) ���
	void write_time(double x)
	{
		fprintf(bur, " ");
		write_type(ext_cls::TIME);
		/*fwrite(&x, sizeof(x), 1, bur);*/
		fprintf(bur, " %f sec", x);
	}
	// �������� ����������� �������, ������ ������������� ���������� ���������
	void write_memory(unsigned long long x)
	{
		write_type(ext_cls::MEMORY);
		/*fwrite(&x, sizeof(x), 1, bur);*/
		fprintf(bur, "%llu", x);
	}
};
////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[])
{
	result checker_result;

	FILE * res_file = fopen((".\\tests\\" + std::string(argv[1]) + ".ans").c_str(), "rb");
	FILE * ans_file = fopen((".\\tests\\" + std::string(argv[1]) + "_true.ans").c_str(), "rb");

	// ����� ������ ��������� ��������� � ����
	double ans_time, res_time;
	// ��������� ����� ������ ��������� ��������� � ����
	fread(&res_time, sizeof(res_time), 1, res_file);
	fread(&ans_time, sizeof(res_time), 1, ans_file);
	// ����������� �������
	int n;
	// ��������� ����������� �������
	fread(&n, sizeof(n), 1, res_file);
	fseek(ans_file, sizeof(n), SEEK_CUR);
	// �������� ������ ��� ������� ������ ���� � ������ ���������
	vector<int> res(n), ans(n);
	// ��������� ������ ���������
	fread(res.data(), sizeof(int), n, res_file);
	// ��������� ������ ����
	fread(ans.data(), sizeof(int), n, ans_file);
	// ���� ��������� �������
	bool isEqual = true;
	// ���� ������������
	for (size_t i = 0; i < n && isEqual; ++i)
		if (res[i] != ans[i])
			isEqual = false;
	// ���������, ��� ������ ���, ����� ��������, ��� ������� ���������, ����� - �����������.
	if (isEqual)
	{
		checker_result.write_message("test #" + string(argv[1]) + ": AC. Numbers are equal. ");
		checker_result.write_verdict(verdict::AC);
	}
	else
	{
		checker_result.write_message("test #" + string(argv[1]) + ": WA. Output is not correct. ");
		checker_result.write_verdict(verdict::WA);
	}
	// ���������� �����
	checker_result.write_time(res_time);

	fclose(res_file);
	fclose(ans_file);
	return 0;
}