#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include <vector>
#include <ccomplex>
#include <ctime>

using namespace std;

vector<vector<complex<int>>> ToStandart(complex<int>* elements,int* secondIndex,int* position,int size)
{
	vector<vector<complex<int>>> standart(size);
	for (int i = 0; i < size; i++)
	{
		standart[i].resize(size);
	}
	for (int i = 0; i < size; ++i)
	{
		int pos = position[i];
		while (pos < position[i + 1])
		{
			standart[i][secondIndex[pos]] = elements[pos];
			pos++;
		}
	}
	return standart;
}

void WriteAnswer(char* input,char* output)
{
	int size, notNull1, notNull2;
	complex<int>* elements1, *elements2;
	int *secondIndex1, *secondIndex2, *position1, *position2;

	freopen(input, "rb", stdin);
	freopen(output, "wb", stdout);

	fread(&size, sizeof(size), 1, stdin);
	fread(&notNull1, sizeof(notNull1), 1, stdin);

	elements1 = new complex<int>[notNull1];
	secondIndex1 = new int[notNull1];
	position1 = new int[size + 1];

	fread(elements1, sizeof(*elements1), notNull1, stdin);
	fread(secondIndex1, sizeof(*secondIndex1), notNull1, stdin);
	fread(position1, sizeof(*position1), size + 1, stdin);

	fread(&notNull2, sizeof(notNull2), 1, stdin);

	elements2 = new complex<int>[notNull2];
	secondIndex2 = new int[notNull2];
	position2 = new int[size + 1];

	fread(elements2, sizeof(*elements2), notNull2, stdin);
	fread(secondIndex2, sizeof(*secondIndex2), notNull2, stdin);
	fread(position2, sizeof(*position2), size + 1, stdin);

	vector<vector<complex<int>>> matrix1 = ToStandart(elements1, secondIndex1, position1,size);
	vector<vector<complex<int>>> matrix2 = ToStandart(elements2, secondIndex2, position2, size);

	vector<vector<complex<int>>> result(size);
	for (int i = 0; i < size; i++)
	{
		result[i].resize(size);
	}

	double time = clock();
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			for (int iter = 0; iter < size; ++iter)
			{
				result[i][j] += matrix1[i][iter] * matrix2[iter][j];
			}
		}
	}
	double timeF = clock() - time;
	fwrite(&timeF, sizeof(timeF), 1, stdout);
	fwrite(&size, sizeof(size), 1, stdout);
	for (int i = 0; i < result.size(); ++i)
		fwrite(result[i].data(), sizeof(result[i][0]), result.size(), stdout);

	
}


