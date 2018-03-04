#ifndef TEST_VERSION_TALAMANOV_A_SHELLSORT_H
#define TEST_VERSION_TALAMANOV_A_SHELLSORT_H 

#include <iterator>
#include <vector>

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

std::vector<int> getSedgwickDistances(int size_array)
{
    std::vector<int> distances;
    int s = 0;
    do{
        distances.emplace_back(getSedgwickElement(s));
        ++s;
    } while(3 * distances.back() < size_array);
    distances.pop_back();
    return distances;
}

template<typename Iterator>
void ShellSort(Iterator first, Iterator last)
{
	if (!(first < last))
		return;

	int  size_array     = std::distance(first, last);
	auto distances      = getSedgwickDistances(size_array);

	std::for_each(distances.rbegin(), distances.rend(),
				[&first, &last](const auto& gap){
					InsertSortWithGap(first, last, gap);
				});
}

#endif //TEST_VERSION_TALAMANOV_A_SHELLSORT_H
