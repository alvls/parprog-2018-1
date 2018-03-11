#include <cstdio> 
#include <cmath> 
#include <string>
#include <iostream>
#include <string>

using namespace std;

void StringName_to_CharName(string str, char* ch);
int Order(int num);
/* 
// Checker ������������� ��� �������� 
AC = Accepted(��������� ���������)
WA = Wrong Answer(��������� �����������)
*/

enum verdict { NO = 1, AC, WA};

class Result 
{
private: 
	FILE * res; 
public: 

	enum type { NO = 1, VERDICT, MESSAGE, TIME, MEMORY }; 

	// �-� �� ���������
	Result(bool read = false)
	{ 
		if (read) 
			fopen_s(&res, "result.txt", "r"); 
		else 
			fopen_s(&res,"result.txt", "w"); 
	}
	// �-�
	~Result() { fclose(res); }
	// ������ ���� ���������
	void write_type(type t) 
	{ 
		//char ch = static_cast<int>(t) + '0';
		//fwrite(&ch, sizeof(char), 1, res);

		fwrite(&t, sizeof(t), 1, res);
	}

	// �������� ����������� �������, ��� ���������� ���� �� ���������
	void write_verdict(verdict v) 
	{
		write_type(type::VERDICT);
		//char ch = static_cast<int>(v) + '0';
		//fwrite(&ch, sizeof(char), 1, res);

		fwrite(&v, sizeof (v), 1, res); 
	}
	
	// �������� ��������� ������������ � ������������ �������
	void write_message(string str)
	{ 
		write_type(type::MESSAGE); 
		int l = str.size ();
		//int order = Order(l);
		//char* ch = new char[order];
		//_itoa_s(l, ch, str.size(), 10);
		//fwrite(ch, sizeof (char), order, res);

		fwrite(&l, sizeof(l), 1, res);
		fwrite (&str[0], sizeof (str[0]), l, res); 
	}

	// �������� ����������� ������� ����� ������ ��������� ���������,  
	// x ����� ����������� 100 �� = 10 ^ (-7) ��� 
	void write_time(double x)
	{ 
		write_type(type::TIME);

		int order = Order(x);
		char* ch = new char[order];
		_itoa_s(x, ch, 100, 10);
		fwrite(ch, sizeof (char), order + 1, res);

		//fwrite(&x, sizeof (x), 1, res); 
	}

} checker_result; 


int main(int argc, char * argv[])
{ 
	// ����� ������
	char* fileIN = "matr.in";
	char* fileOUT = "matr.out";
	char* answer = "answer.ans";

	if (argc > 1)
	{
		// ��������� ����� ��� ����� � ���������
		fileIN = argv[1];
		// ��������� ����� ��� ��������� �����
		string str = string(argv[1]) + string(".out");
		fileOUT = new char[str.length()];
		StringName_to_CharName(str, fileOUT);
		str = string(argv[1]) + string(".ans");
		answer = new char[str.length()];
		StringName_to_CharName(str, answer);
	}


	// ��������� ���� ������� ������,  ����� ��������� 
	FILE * bui;
	fopen_s(&bui, fileIN, "rb");
	FILE * buo;
	fopen_s(&buo, fileOUT, "rb");
	// ��������� ������
	FILE * perfect;
	fopen_s(&perfect, answer, "rb");
	



	int N; 
	// ��������� ����������� ������ 
	fread(&N, sizeof (N), 1, bui);

	int block_size; 
	// ��������� ������ �����
	fread(&block_size, sizeof(block_size), 1, bui);

	// �������� ������ ��� ������� ������ ���� � ������ ���������
	double **ans = new double*[N];
	for (int count = 0; count < N; count++)
		ans[count] = new double[N];

	double **res = new double*[N];
	for (int count = 0; count < N; count++)
		res[count] = new double[N];

	// ������� ������ ���� � ��������� 
	double ans_time, res_time;
	
	// ��������� ����� ������ ��������� ��������� � ������� ��������� 
	for (int i = 0; i < N; i++)
	{
		fread(ans[i], sizeof(double), N, buo);
	}
	fread(&ans_time, sizeof(double), 1, buo);
  
	// ��������� ����� ������ ��������� � ������� ���� 
	for (int i = 0; i < N; i++)
	{
		fread(res[i], sizeof(double), N, perfect);
	}
	fread(&res_time, sizeof(double), 1, perfect);

	bool flag = true;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (res[i][j] != ans[i][j])
			{
				flag = false;
				break;
			}
		}
	}

		   
	// ���� ������ ���, �������� ��� ������� ���������
	if (flag)
	{ 
		checker_result.write_message ("AC. Numbers are equal.");
		checker_result.write_verdict (verdict::AC); 
	} 
	else 
	{ 
		checker_result.write_message ("WA. Output is not correct."); 
		checker_result.write_verdict (verdict::WA); 
	}
		   
	// ��������� �����, ��� 
	checker_result.write_time (res_time);

	fclose(buo);
	fclose(bui);
	fclose(perfect);

	return 0;
}

void StringName_to_CharName(string str, char* ch)
{
	for (int i = 0; i < str.length(); i++)
		ch[i] = str[i];
}

int Order(int num)
{
	int order = 0;

	while (num) 
	{
		num /= 10;
		order++;
	}

	return order;
}