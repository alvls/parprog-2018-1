#ifndef TALAMANOV_AE_TEST_VERSION_SHELLSORT_H
#define TALAMANOV_AE_TEST_VERSION_SHELLSORT_H

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

#endif //TALAMANOV_AE_TEST_VERSION_SHELLSORT_H
