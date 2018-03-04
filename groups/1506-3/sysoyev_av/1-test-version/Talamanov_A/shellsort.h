#ifndef TEST_VERSION_TALAMANOV_A_SHELLSORT_H
#define TEST_VERSION_TALAMANOV_A_SHELLSORT_H 

#include <iterator>

template<typename Iterator>
void InsertSortWithGap(Iterator first, Iterator last, int gap)
{
	int tmp;
	int j;
	int size_array = std::distance(first, last);

	for(int i = gap; i < size_array; ++i ){
		tmp = *(first + i);
		j = i;
		while(j >= gap && tmp < *(first + j - gap)){
			*(first + j) = *(first + j - gap);
			j -= gap;
		}
		*(first + j) = tmp;
	}
}

int getSedgwickElement(int s)
{
	return (s % 2 == 0) ? (9 * (1 << s)	- 9 * (1 <<  (s / 2)     ) + 1)
		                : (8 * (1 << s) - 6 * (1 << ((s + 1) / 2)) + 1);
}
#endif //TEST_VERSION_TALAMANOV_A_SHELLSORT_H
