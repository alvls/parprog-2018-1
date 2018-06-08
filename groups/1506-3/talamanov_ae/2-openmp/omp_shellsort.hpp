#ifndef GROUPS_1506_3_TALAMANOV_AE_2_OPENMP_OMP_SHELLSORT_HPP_
#define GROUPS_1506_3_TALAMANOV_AE_2_OPENMP_OMP_SHELLSORT_HPP_

#include <vector>
#include <utility>
#include "shellsort.hpp"

template<typename Iterator>
void OmpShellSort(Iterator first, Iterator last, size_t thread_count = 1) {
  typedef typename iterator_traits<Iterator>::value_type type;
  omp_set_num_threads(thread_count);
  size_t chunk = std::distance(first, last) / thread_count;
  Iterator f, l;
  std::vector<std::pair<Iterator, Iterator>> ranges(thread_count);

#pragma omp parallel for schedule(static) shared(first, chunk, ranges) \
  private(f, l)
  for (int i = 0; i < thread_count; ++i) {
    f = first + i * chunk;
    l = (i == thread_count - 1) ? last : f + chunk;
    ranges[i] = std::make_pair(f, l);
    ShellSort(f, l);
  }

  int merge_count = thread_count / 2;
  int scale = 2;
  int shift = 0;
  int start_idx;
  Iterator start, mid, end;

  while (merge_count) {
#pragma omp parallel for schedule(dynamic) \
    private(start_idx, start, mid, end) shared(scale, ranges)
    for (int i = 0; i < merge_count; ++i) {
      start_idx = i * scale;
      start = ranges[start_idx].first;
      mid   = ranges[start_idx + pow(2, shift)].first;
      end   = ranges[start_idx + pow(2, shift + 1) - 1].second;

      std::inplace_merge(start, mid, end);
    }
    merge_count /= 2;
    scale *= 2;
    shift++;
  }
}

#endif  // GROUPS_1506_3_TALAMANOV_AE_2_OPENMP_OMP_SHELLSORT_HPP_
