#include <tbb/tbb.h>

unsigned char GetByte(const double* number, const unsigned digit_num) {
	return (reinterpret_cast<const unsigned char*>(number))[digit_num];
}

void LsdRadixSortPartial(double* arr, double* arr_temp, const size_t arr_size) {
	const int kDigitsNumber = 8;
	const size_t kDigitPossibleValuesNumber = 256;
	const size_t kDigitPossibleValuesNumberHalf = kDigitPossibleValuesNumber >> 1;

	int* counters = new int[kDigitPossibleValuesNumber];

	for (int i = 0; i < kDigitsNumber; i++) {
		// Basically this checks if this is the last iteration
		// (or if the current digit is a most significant one)
		const bool is_curr_digit_msd = i == kDigitsNumber - 1;

		for (size_t j = 0; j < kDigitPossibleValuesNumber; j++) {
			counters[j] = 0;
		}

		// Counting sort
		for (size_t j = 0; j < arr_size; j++) {
			const unsigned char curr_digit_unsigned = GetByte(&arr[j], i);
			counters[curr_digit_unsigned]++;
		}

		int count = 0;

		if (is_curr_digit_msd) {
			// Counting all negative numbers
			for (size_t j = kDigitPossibleValuesNumberHalf; j < kDigitPossibleValuesNumber; j++) {
				count += counters[j];
			}

			// Only for non-negative numbers
			for (size_t j = 0; j < kDigitPossibleValuesNumberHalf; j++) {
				const int temp = counters[j];
				counters[j] = count;
				count += temp;
			}

			count = 0;

			// Counters for negative numbers in reverse
			for (size_t j = kDigitPossibleValuesNumber - 1; j >= kDigitPossibleValuesNumberHalf; j--) {
				counters[j] += count;
				count = counters[j];
			}
		} else {
			for (size_t j = 0; j < kDigitPossibleValuesNumber; j++) {
				const int temp = counters[j];
				counters[j] = count;
				count += temp;
			}
		}

		for (size_t j = 0; j < arr_size; j++) {
			const unsigned char curr_digit_unsigned = GetByte(&arr[j], i);

			// "If current number is negative"
			if (is_curr_digit_msd && curr_digit_unsigned >= kDigitPossibleValuesNumberHalf) {
				arr_temp[--counters[curr_digit_unsigned]] = arr[j];
			} else {
				arr_temp[counters[curr_digit_unsigned]++] = arr[j];
			}
		}

		for (size_t j = 0; j < arr_size; j++) {
			arr[j] = arr_temp[j];
		}
	}

	delete[] counters;
}

// Modified binary search to always return something + searches within [left_bound;right_bound)
int BinarySearch(const double* arr, const int left_bound, const int right_bound, const double elem) {
	int left = left_bound;
	int right = right_bound - 1;
	int middle;

	if (elem < arr[left]) {
		return left;
	} else if (elem > arr[right]) {
		return right;
	}

	while (left <= right) {
		middle = left + (right - left) / 2;

		const double middle_elem = arr[middle];

		if (elem < middle_elem) {
			right = middle - 1;
		} else if (elem > middle_elem) {
			left = middle + 1;
		} else {
			return middle;
		}
	}

	return left;
}

// Spawned by LsdRadixSortTask
class DacMergeTask : public tbb::task {
public:
	DacMergeTask(const double* arr1, const double* arr2, double* arr_temp, const size_t arr_size_1, const size_t arr_size_2) : arr1_(arr1), arr2_(arr2), arr_temp_(arr_temp), arr_size_1_(arr_size_1), arr_size_2_(arr_size_2) {}

	tbb::task* execute() {
		int curr_index_first = 0;
		int curr_index_second = 0;
		int curr_index_sorted = 0;

		while (curr_index_first < arr_size_1_) {
			while (curr_index_second < arr_size_2_ && arr2_[curr_index_second] < arr1_[curr_index_first]) {
				arr_temp_[curr_index_sorted] = arr2_[curr_index_second];
				curr_index_second++;
				curr_index_sorted++;
			}

			arr_temp_[curr_index_sorted] = arr1_[curr_index_first];
			curr_index_first++;
			curr_index_sorted++;
		}

		while (curr_index_second < arr_size_2_) {
			arr_temp_[curr_index_sorted] = arr2_[curr_index_second];
			curr_index_second++;
			curr_index_sorted++;
		}

		return nullptr;
	}

private:
	const double* arr1_;
	const double* arr2_;
	double* arr_temp_;
	const size_t arr_size_1_;
	const size_t arr_size_2_;
};

class LsdRadixSortTask : public tbb::task {
public:
	LsdRadixSortTask(double* arr, double* arr_temp, const size_t arr_size, const size_t arr_part_size) :
		arr_(arr), arr_temp_(arr_temp), arr_size_(arr_size), arr_part_size_(arr_part_size) {}

	tbb::task* execute() {
		if (arr_size_ <= arr_part_size_) {
			LsdRadixSortPartial(arr_, arr_temp_, arr_size_);
			return nullptr;
		}

		// Need to split the array, create & spawn tasks
		LsdRadixSortTask& sort_task_1 = *(new(allocate_child()) LsdRadixSortTask(
			arr_,
			arr_temp_,
			arr_size_ / 2,
			arr_part_size_
		));
		LsdRadixSortTask& sort_task_2 = *(new(allocate_child()) LsdRadixSortTask(
			arr_ + arr_size_ / 2,
			arr_temp_ + arr_size_ / 2,
			arr_size_ - arr_size_ / 2,
			arr_part_size_
		));

		set_ref_count(2 + 1); // two tasks above + 1
		spawn(sort_task_1);
		spawn_and_wait_for_all(sort_task_2);

		// At this point our current part of the initial array consists of two separate sorted parts.
		// Let's merge it via DAC merge
		
		const int middle_first_offset = arr_size_ / 4;

		const double* middle_first = arr_ + middle_first_offset;
		const double* middle = arr_ + arr_size_ / 2;

		const int middle_second_offset = BinarySearch(
			middle,
			0,
			arr_size_ / 4,
			*middle_first
		);

		const double* middle_second = middle + middle_second_offset;

		DacMergeTask& merge_task_1 = *(new(allocate_child()) DacMergeTask(
			arr_,
			middle,
			arr_temp_,
			middle_first_offset + 1,
			middle_second_offset + 1
		));
		DacMergeTask& merge_task_2 = *(new(allocate_child()) DacMergeTask(
			middle_first,
			middle_second,
			arr_temp_ + (middle_first_offset + 1) + (middle_second_offset + 1),
			(arr_size_ / 2) - (middle_first_offset + 1),
			(arr_size_ / 2) - (middle_second_offset + 1)
		));

		set_ref_count(1 + 2);
		spawn(merge_task_1);
		spawn_and_wait_for_all(merge_task_2);

		for (int i = 0; i < arr_size_; i++) {
			arr_[i] = arr_temp_[i];
		}

		return nullptr;
	}

private:
	double* arr_;
	double* arr_temp_;
	const size_t arr_size_;
	const size_t arr_part_size_;
};

void LsdRadixSort(double* arr, const size_t arr_size, int num_threads) {
	if (arr_size == 1) {
		return;
	}

	if (num_threads == 1 || num_threads > (int)arr_size) {
		num_threads = 2;
	}

	double* arr_temp = new double[arr_size];
	size_t arr_part_size = arr_size / num_threads;

	if (arr_size % num_threads != 0) {
		arr_part_size++;
	}

	tbb::task_scheduler_init init(num_threads);

	LsdRadixSortTask& sort_task = *(new(tbb::task::allocate_root()) LsdRadixSortTask(
		arr, arr_temp, arr_size, arr_part_size
	));

	tbb::task::spawn_root_and_wait(sort_task);

	init.terminate();

	delete[] arr_temp;
}
