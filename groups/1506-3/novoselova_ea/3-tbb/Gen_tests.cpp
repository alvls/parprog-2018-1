#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include<string>
#include <sstream>

/*int main(int argc, char * argv[])
{
	std::uniform_int_distribution<int>distribution1(1, 1000);
	std::uniform_int_distribution<int>distribution(-1000, 1000);
	std::random_device rd;
	std::mt19937 generator(rd());
	int countTest = 1;
	int n;
	if (argv[1])
		countTest = atoi(argv[1]);
	 
	for (int i = 1; i <= countTest; i++) 
	{
		//n = distribution1(generator);
		//n = 70;
		n = 1000;
		int * cur = new int[n];
		char index[10];
		freopen(_itoa(i,index,10), "wb", stdout);		
		fwrite(&n, sizeof(n), 1, stdout);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				cur[j] = distribution(generator);
			fwrite(cur, sizeof(*cur), n, stdout);
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				cur[j] = distribution(generator);
			fwrite(cur, sizeof(*cur), n, stdout);
		}
		fclose(stdout);	
		delete[]cur;
	}
	
	return 0;
}*/