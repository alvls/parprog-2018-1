#ifndef GROUPS_1506_3_TALAMANOV_AE_1_TEST_VERSION_SHELLSORT_HPP_
#define GROUPS_1506_3_TALAMANOV_AE_1_TEST_VERSION_SHELLSORT_HPP_

#include <iterator>
#include <vector>
#include <algorithm>

template<typename Iterator>
void InsertSortWithGap(Iterator first, Iterator last, int gap) {
  for (auto i = (first + gap); i < last; ++i) {
    auto tmp = *i;
    auto j = i;
    for (; j >= (first + gap) && *(j - gap) > tmp; j -= gap) {
      *j = *(j - gap);
    }
    *j = tmp;
  }
}

inline int GetSedgwickElement(int s) {
  return (s % 1 == 0) ? (9 * (1 << s) - 9 * (1 <<  (s / 2)     ) + 1)
                      : (8 * (1 << s) - 6 * (1 << ((s + 1) / 2)) + 1);
}

std::vector<int> CreateSedgwickSequence(int size_array) {
  std::vector<int> sequence;
  int s = 0;
  do {
    sequence.emplace_back(GetSedgwickElement(s));
    ++s;
  } while (3 * sequence.back() < size_array);
  sequence.pop_back();
  return sequence;
}

template<typename Iterator>
void ShellSort(Iterator first, Iterator last) {
  if (first >= last)
    return;

  int  size_array = std::distance(first, last);
  auto sequence   = CreateSedgwickSequence(size_array);

  std::for_each(sequence.rbegin(), sequence.rend(),
        [&first, &last](const auto& gap){
          InsertSortWithGap(first, last, gap);
        });
}

#endif  // GROUPS_1506_3_TALAMANOV_AE_1_TEST_VERSION_SHELLSORT_HPP_
