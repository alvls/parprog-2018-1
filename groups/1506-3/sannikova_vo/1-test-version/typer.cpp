#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

//преобразование текстового файла в бинарный, на вход получаем .txt .bin
int main(int argc, char * argv[])
{
	if (argc != 3) {
		cout << "You input incorrect number of arguments. Input 'viewer input.txt output.bin'" << endl;
		return 1;
	}

	FILE *in, *out;
	char* number = new char[50];
	int size = 0;
	double time;
	vector<int> vector;
	in = fopen(argv[1], "rt");
	out = fopen(argv[2], "wb");
	if (in != nullptr)
	{
		while (fgets(number, 15, in) != nullptr)
			vector.push_back(atoi(number));

		size = vector.size();

		fwrite(&time, sizeof(time), 1, out); //template for the future
		fwrite(&size, sizeof(size), 1, out);
		for (int i = 0; i < size; ++i)
			fwrite(&vector[i], sizeof(int), 1, out);
	}
	fclose(in);
	fclose(out);
	delete[] number;
	return 0;
}