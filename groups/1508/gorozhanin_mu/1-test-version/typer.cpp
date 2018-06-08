#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;


int main(int argc, char * argv[])
{
	if (argc != 3) {
		cout << "You use the \"Typer\" to process data. Enter the arguments in the correct format !!" << endl;
		return 1;
	}

	char* number_int = new char[15];
	int size = 0;
	double start_time=0;
	vector<int> check;
	FILE *in_txt = fopen(argv[1], "rt");
	FILE *out_bin = fopen(argv[2], "wb");
	if (in_txt != nullptr)
	{
		//ѕреобразуем строку т.е. каждое отдельное число типа int, и "пушим" его как значение типа int в конец вектора.
		while (fgets(number_int, 15, in_txt) != nullptr)
			check.push_back(atoi(number_int));
		// ‘иксируем размер вектора в бинарном формате.
		size = check.size();

		fwrite(&start_time, sizeof(start_time), 1, out_bin);
		fwrite(&size, sizeof(size), 1, out_bin);
		for (int i = 0; i < size; ++i)
			fwrite(&check[i], sizeof(int), 1, out_bin);
	}
	fclose(in_txt);
	fclose(out_bin);
	delete[] number_int;
	return 0;
}