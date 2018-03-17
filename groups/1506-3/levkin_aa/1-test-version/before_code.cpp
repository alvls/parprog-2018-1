#include <fstream>
#include <string>

#include <omp.h>
using namespace std;

void qsortBatcher(int* a, int size);

int _tmain(int argc, _TCHAR* argv[])
{
	//значени€ по умолчанию, если запуск не через скрипт
	int n = 20;
	int sizeMass = 256;
	string nameFile;

	if (argc == 2)
	{
		n = (int)(stod(argv[1]));// = stoi(argv[1]);
	}

	for(int i=1;i<=n;i++)
	{
		nameFile =to_string((long long)i);
		FILE* fTestMass = fopen(("./tests/"+ nameFile).c_str(), "rb");
		FILE* fResMass = fopen(("./tests/"+ nameFile + ".ans").c_str(), "wb");

		//считывание размера и сам массив
		fread(&sizeMass, sizeof (sizeMass), 1, fTestMass);
		int *data=new int[sizeMass];
		fread(data, sizeof (*data), sizeMass, fTestMass);
		
		auto timeWork = omp_get_wtime();
		qsortBatcher(data, sizeMass);
		timeWork = omp_get_wtime() - timeWork;

		//записываем все данные в файл(размер вермм€ работы и сам массив)
		fwrite(&sizeMass, sizeof(sizeMass), 1, fResMass);
		fwrite(&timeWork, sizeof(timeWork), 1, fResMass);
		fwrite(data, sizeof (*data), sizeMass, fResMass);

		delete []data;
		fclose(fTestMass);
		fclose(fResMass);
	}
	return 0;
	
}

