#include <cstdio>
#include <iostream>

int main(int argc, char * argv[]) {
	freopen("../tests/5.ans", "wb", stdout);
	 
	double result = 0.0;

	fwrite(&result, sizeof(double), 1, stdout);

	return 0;
}