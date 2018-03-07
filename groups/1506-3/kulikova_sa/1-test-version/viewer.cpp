#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include "Sole.h"

//Отображает бинарный файл
//argv[1] - имя входного файла
int viewer(int argc, char * argv[]) {
	if (argc != 3) {
		std::cout << "Некорректные данные" << std::endl;
		return 1;
	}

	freopen(argv[1], "rb", stdin);

	int N;

	fread(&N, sizeof(N), 1, stdin);

	Sole * S = new Sole(N);

	for (int i = 0; i < N; i++)
		fread(S->A[i], sizeof(**(S->A)), N, stdin);
	fread(S->b, sizeof(*(S->b)), N, stdin);
	fread(S->x, sizeof(*(S->x)), N, stdin);

	S->Print();

	return 0;
}