#include <cstdio>
#include <iostream>
#include <iostream>

int main() {
	double result = 0.0;
	char way[31] = "../../simple-vers/tests/40.ans";
	for (char a = '0'; a < '9' + 1; a++) {
		way[25] = a;
		std::cout << way;
		freopen(way, "rb", stdin);
		fread(&result, sizeof(result), 1, stdin);
		std::cout << " " <<result << std::endl;
		fclose(stdin);
	}
	
	system("pause");

	return 0;

}