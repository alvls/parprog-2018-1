/* ��������� viewer.cpp �������� �� ���� ��� ����� �
����������� ��� ���������� �� ��������� ���� � ���������.*/
#include <string>
#include <fstream>

int main(int argc, char * argv[])
{
	std::string filename;
	std::ofstream textfile;
	std::ifstream binfile;

	int N;
	int tmp;
	double time;

	if (argc <= 1)
		return 0;
	else
		filename = argv[1];

	binfile.open(filename, std::ios::binary);
	if (!binfile.is_open())
		return 0;

	if (filename.find(".\\") == 0)
		filename.erase(0, 2);

	textfile.open(filename.substr(0, filename.find('.')) + "_out.txt");

	binfile.read((char*)(&time), sizeof(double)); // ���������� �������
	binfile.read((char*)(&N), sizeof(int));

	textfile << time << " " << N;

	for (size_t i = 0; i < N; ++i)
	{
		binfile.read((char*)(&tmp), sizeof(int));
		textfile << " " << tmp;
	}

	textfile.close();
	binfile.close();
}