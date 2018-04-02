#ifndef GROUPS_1506_3_TALAMANOV_AE_3_TBB_TBB_SHELLSORT_HPP_
#define GROUPS_1506_3_TALAMANOV_AE_3_TBB_TBB_SHELLSORT_HPP_

#include <iostream>
#include <algorithm>
#include <iterator>
#include "tbb/tbb.h"
#include "../1-test-version/shellsort.hpp"

template<typename Iterator>
void TbbShellSort(Iterator first, Iterator last, size_t thread_count = 1) {
	typedef typename std::iterator_traits<Iterator>::value_type type;
	tbb::task_scheduler_init init(thread_count);
	size_t chunk = std::distance(first, last) / thread_count;
	std::vector<std::pair<Iterator, Iterator>> ranges(thread_count);

	parallel_for(tbb::blocked_range<int>(0, thread_count), 
			[&chunk, &ranges, &first, &last, &thread_count](const tbb::blocked_range<int>& r) {
				for (int i = r.begin(); i < r.end(); ++i) {
					auto f = first + i * chunk;
					auto l = (i == thread_count - 1) ? last : f + chunk;
					ranges[i] = std::make_pair(f, l);
					ShellSort(f, l);
					//std::copy(f, l, std::ostream_iterator<type>(std::cout, " "));
					//std::cout << std::endl;
				} 
			}
	);

	int merge_count = thread_count / 2;
	int scale = 2;
	int shift = 0;
	Iterator start, mid, end;

	while (merge_count) {
		parallel_for(tbb::blocked_range<int>(0, merge_count),
				[=](const tbb::blocked_range<int>& r) {
					for (int i = 0; i < merge_count; ++i) {
						int start_idx = i * scale;
						auto start = ranges[start_idx].first;
						auto mid   = ranges[start_idx + pow(2, shift)].first;
						auto end   = ranges[start_idx + pow(2, shift + 1) - 1].second;

						std::inplace_merge(start, mid, end);
		    }
		});
		merge_count /= 2;
		scale *= 2;
		shift++;
	}
}

#endif  // GROUPS_1506_3_TALAMANOV_AE_3_TBB_TBB_SHELLSORT_HPP_
