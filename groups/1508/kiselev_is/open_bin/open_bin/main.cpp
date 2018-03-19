#include <cstdio>
#include <iostream>


int main() {
	double result = 0.0;
	freopen("../../simple-vers/tests/10.ans", "rb", stdin);
	fread(&result, sizeof(result), 1, stdin);
	std::cout << result;

	system("pause");
	return 0;

}