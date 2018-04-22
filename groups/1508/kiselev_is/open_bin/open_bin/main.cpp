#include <cstdio>
#include <iostream>
#include <iostream>

int main() {
	double result = 0.0;
	double time = 0.0;
	char way[31] = "../../simple-vers/tests/50.ans";
	for (char a = '0'; a <= '9'; a++) {
		way[25] = a;
		freopen(way, "rb", stdin);
		fread(&result, sizeof(result), 1, stdin);
		fread(&time, sizeof(result), 1, stdin);
		std::cout << way <<" " << result << " " << time << std::endl;
		fclose(stdin);
	}
		
	
	system("pause");

	return 0;

}