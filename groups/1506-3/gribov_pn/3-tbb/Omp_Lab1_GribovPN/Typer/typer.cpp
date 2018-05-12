/* Программа typer.cpp получает на вход имя текстового файла 
(через аргумент командой строки), в котором записаны 
входные данные в текстовом виде, и преобразует их в бинарный вид. */
#include <string>
#include <fstream>

int main(int argc, char * argv[])
{
	std::string filename;
	std::ifstream textfile;
	std::ofstream binfile;

	int N;
	int tmp;

	if (argc <= 1)
		return 0;
	else
		filename = argv[1];

	textfile.open(filename);
	if (!textfile.is_open())
		return 0;

	if (filename.find(".\\") == 0)
		filename.erase(0, 2);

	binfile.open(filename.substr(0, filename.find('.')) + ".mybin", std::ios::binary);

	textfile >> N;

	//binfile.write((char*)(&N), sizeof(int));  //вместо времени для первичных тестов

	binfile.write((char*)(&N), sizeof(int));

	for (size_t i = 0; i < N; ++i)
	{
		textfile >> tmp;
		binfile.write((char*)(&tmp), sizeof(int));
	}

	textfile.close();
	binfile.close();
}
