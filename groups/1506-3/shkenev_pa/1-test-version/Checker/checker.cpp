#include <fstream>
#include <cmath>
#include "Result.h"

#define ACCURACY 4

int main(int argc, char *argv[])
{
	int width, height; // ������� ������������� �����������
	int mWidth, mHeight; // ������� ���������� �����������
	bool correct = true; // �����������, ��� ������� �����
	Result result;
	std::ifstream fAnswer(argv[1], std::ios::binary); // ���� � ������������ ��������
	std::ifstream fModel(argv[2], std::ios::binary); // ���� � ���������� ��������

	// ������ �������� �����������
	fAnswer.read((char *)&width, sizeof(width));
	fAnswer.read((char *)&height, sizeof(height));
	fModel.read((char *)&mWidth, sizeof(mWidth));
	fModel.read((char *)&mHeight, sizeof(mHeight));

	if (width != mWidth || height != mHeight)
	{ // ������� �� ���������
		correct = false;
		fAnswer.close();
		fModel.close();
	}
	else
	{
		double time; // �����, ����������� �� �����
		int imageLength = width * height * 3;

		// ������ ������������� �������
		unsigned char *answer = new unsigned char[imageLength];
		fAnswer.read((char *)answer, imageLength);
		fAnswer.read((char *)&time, sizeof(time));
		fAnswer.close();
		
		// ������ ���������� �����������
		unsigned char *model = new unsigned char[imageLength];
		fModel.read((char *)model, imageLength);
		fModel.close();

		result.write_time(time * 1e7);

		// ��������� �����������
		for (int i = 0; i < imageLength; i++)
		{
			if (std::abs(answer[i] - model[i]) > ACCURACY)
			{
				correct = false;
				break;
			}
		}

		delete[] answer;
		delete[] model;
	}

	if (correct)
	{
		result.write_message("AC. Images are equal.");
		result.write_verdict(AC);
	}
	else
	{
		result.write_message("WA. Images are not equal. Answer is not correct.");
		result.write_verdict(WA);
	}

	return 0;
}
