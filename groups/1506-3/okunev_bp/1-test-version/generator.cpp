#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <random>
#include <ctime>
#include <chrono> 
#include <vector>

using std::vector;

const int DEFAULT_MATRIX_SIZE = 1000;
const double DENSITY = 0.1; //10%

int main(int argc, char* argv[])
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distribution(- 1000, 1000);

	char* PATHin = "matr.in";
	int matrixSize = DEFAULT_MATRIX_SIZE;
	int notZero = 0;
	int testType = 0;

	vector<double> value;
	vector<int> col;
	vector<int> row(matrixSize + 1);


	int notZeroB = 0;
	vector<double> valueB;
	vector<int> colB;
	vector<int> rowB(matrixSize + 1);

	if (argc > 1)
	{
		PATHin = argv[1];
		if (argc > 3)
		{
			matrixSize = atoi(argv[2]);
			if (argc > 4)
				testType = atoi(argv[3]);
		}
	}

	int elemToRow = matrixSize * DENSITY;

	value.reserve(matrixSize * elemToRow);
	col.reserve(matrixSize * elemToRow);

	valueB.reserve(matrixSize * elemToRow);
	colB.reserve(matrixSize * elemToRow);

	freopen(PATHin, "wb", stdout);

	switch (testType)
	{
	case 0:
		int interval = matrixSize / elemToRow;
		std::uniform_int_distribution<int> distributionInt(0, interval - 1);
		for (int i = 0; i < matrixSize; ++i)
		{
			vector<int> tmp;
			tmp.reserve(elemToRow);
			for (int j = 0; j < elemToRow; ++j)
			{
				value.emplace_back(distribution(gen));
				tmp.emplace_back(interval * j + distributionInt(gen));
			}
			std::sort(tmp.begin(), tmp.end());
			col.insert(col.end(), tmp.begin(), tmp.end());
			row[i] = i * elemToRow;
		}
		row[matrixSize] = row[matrixSize - 1] + 1;
		notZero = value.size();

		for (int i = 0; i < matrixSize; ++i)
		{
			vector<int> tmp;
			tmp.reserve(elemToRow);
			for (int j = 0; j < elemToRow; ++j)
			{
				valueB.emplace_back(distribution(gen));
				tmp.emplace_back(interval * j + distributionInt(gen));
			}
			std::sort(tmp.begin(), tmp.end());
			colB.insert(colB.end(), tmp.begin(), tmp.end());
			rowB[i] = i * elemToRow;
		}
		rowB[matrixSize] = rowB[matrixSize - 1] + 1;
		notZeroB = valueB.size();
		break;
	}
	
	fwrite(&matrixSize, sizeof(matrixSize), 1, stdout);
	if (notZero == 0)
		throw("Invalid test");
	fwrite(&notZero, sizeof(notZero), 1, stdout);
	fwrite(value.data(), sizeof(value[0]), value.size(), stdout);
	fwrite(col.data(), sizeof(col[0]), col.size(), stdout);
	fwrite(row.data(), sizeof(row[0]), row.size(), stdout);

	fwrite(&matrixSize, sizeof(matrixSize), 1, stdout);
	if (notZeroB == 0)
		throw("Invalid test");
	fwrite(&notZeroB, sizeof(notZeroB), 1, stdout);
	fwrite(valueB.data(), sizeof(valueB[0]), valueB.size(), stdout);
	fwrite(colB.data(), sizeof(colB[0]), colB.size(), stdout);
	fwrite(rowB.data(), sizeof(rowB[0]), rowB.size(), stdout);

	return 0;
}
