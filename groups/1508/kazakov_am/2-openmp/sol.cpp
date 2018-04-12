#include <omp.h>

unsigned char GetByte(const double number, const unsigned digit_num) {
	const long long int_number = static_cast<long long>(number);

	return static_cast<unsigned char>(
		(int_number >> (8 * digit_num)) & 0xFF
	);
}

// Sorts an array within [index_start, index_end) interval
void LsdRadixSortPartial(double* arr,
	double* arr_temp, const size_t arr_size,
	const int index_start, const int index_end){
	const int kDigitsNumber = 8;
	const size_t kDigitPossibleValuesNumber = 256;

	int* counters = new int[kDigitPossibleValuesNumber];

	for (int i = 0; i < kDigitsNumber; i++) {
		// Basically this checks if this is the last iteration
		// (or if the current digit is a most significant one)
		const bool is_curr_digit_msd = i == kDigitsNumber - 1;

		for (size_t j = 0; j < kDigitPossibleValuesNumber; j++) {
			counters[j] = 0;
		}

		// Counting sort
		for (size_t j = index_start; j < index_end; j++) {
			const unsigned char curr_digit_unsigned = GetByte(arr[j], i);
			// For MSD, we should interpret the current byte as a singed char
			const char curr_digit_signed = static_cast<char>(curr_digit_unsigned);
			const unsigned char counters_index = is_curr_digit_msd
				? curr_digit_signed + 128
				: curr_digit_unsigned;
			counters[counters_index]++;
		}

		int count = 0;

		for (size_t j = 0; j < kDigitPossibleValuesNumber; j++) {
			const int temp = counters[j];
			counters[j] = count;
			count += temp;
		}

		for (size_t j = index_start; j < index_end; j++) {
			const unsigned char curr_digit_unsigned = GetByte(arr[j], i);
			const char curr_digit_signed = static_cast<char>(curr_digit_unsigned);
			const unsigned char counters_index = is_curr_digit_msd
				? curr_digit_signed + 128
				: curr_digit_unsigned;
			arr_temp[index_start + counters[counters_index]] = arr[j];
			counters[counters_index]++;
		}

		for (size_t j = index_start; j < index_end; j++) {
			arr[j] = arr_temp[j];
		}
	}

	delete[] counters;
}

// Modified binary search to always return something + searches within [left_bound;right_bound)
int BinarySearch(const double* arr, const int left_bound, const int right_bound, const double elem) {
	const int arr_size = right_bound - left_bound;

	int left = left_bound;
	int right = right_bound - 1;
	int middle;

	if (elem < arr[left]) {
		return left;
	} else if (elem > arr[right]) {
		return right;
	}
	
	while (left < right) {
		middle = (left + right) / 2;

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

// Performs "divide and conquer" "merge" within the array.
void DacMerge(const double* arr_in, double* arr_out, const int iteration, const int* boundaries,
	const int left_bound_first, const int right_bound_first,
	const int left_bound_second, const int right_bound_second) {
	const int arr_len_first = right_bound_first - left_bound_first;
	const int arr_len_second = right_bound_second - left_bound_second;
	const bool merge_first_parts_of_pair = iteration % 2 == 0;

	int curr_index_first = 0;
	int curr_index_second = 0;
	int curr_index_sorted = merge_first_parts_of_pair
		? boundaries[iteration * 4]
		: boundaries[iteration * 2 + 1] - arr_len_first - arr_len_second;
	const int curr_index_sorted_change = merge_first_parts_of_pair ? 1 : -1;

	while (curr_index_first < arr_len_first) {
		while (curr_index_second < arr_len_second
			&& arr_in[left_bound_second + curr_index_second] < arr_in[left_bound_first + curr_index_first]) {
			arr_out[curr_index_sorted] = arr_in[left_bound_second + curr_index_second];
			curr_index_second++;
			curr_index_sorted++;
		}

		arr_out[curr_index_sorted] = arr_in[left_bound_first + curr_index_first];
		curr_index_first++;
		curr_index_sorted++;
	}

	while (curr_index_second < arr_len_second) {
		arr_out[curr_index_sorted] = arr_in[left_bound_second + curr_index_second];
		curr_index_second++;
		curr_index_sorted++;
	}
}

void LsdRadixSortWithDacMerge(double* arr, const size_t arr_size) {
	if (arr_size == 1) {
		return;
	}

	int num_threads = omp_get_num_threads();

	// This checks if number of threads is 1, OR greater than arr_size, OR indivisible by 2^n
	if (num_threads == 1 || num_threads > (int)arr_size || (num_threads & (num_threads - 1))) {
		num_threads = 2;
		omp_set_num_threads(num_threads);
	}

	const size_t arr_part_size = arr_size / num_threads;
	int* boundaries = new int[num_threads * 2];
	// We need this array twice, on both steps. To not allocate memory twice, we do it once, here
	double* arr_temp = new double[arr_size];

	// Step I. Sorting
	#pragma omp parallel shared(arr, arr_temp, arr_part_size, arr_size, num_threads, boundaries)
	{
		const int thread_num = omp_get_thread_num();
		const int index_start = thread_num * arr_part_size;
		int index_end = index_start + arr_part_size;

		// "Last" thread: we must fix index_end
		if (thread_num == num_threads - 1) {
			index_end += arr_size % num_threads;
		}

		boundaries[2 * thread_num] = index_start;
		boundaries[2 * thread_num + 1] = index_end;

		LsdRadixSortPartial(arr, arr_temp, arr_size, index_start, index_end);
	}

	// Step II. Merging
	int array_pairs_num = num_threads / 2;
	int* middle_indexes = new int[num_threads];
	
	while (array_pairs_num != 0) {
		// Merging preparations
		for (int i = 0; i < array_pairs_num; i++) {
			const int left_bound_first = boundaries[i * 4];
			const int right_bound_first = boundaries[i * 4 + 1];
			const int left_bound_second = boundaries[i * 4 + 2];
			const int right_bound_second = boundaries[i * 4 + 3];

			// Find two middle points in the current pair of arrays
			const int middle_index_first = (left_bound_first + right_bound_first) / 2;
			const int middle_index_second = BinarySearch(
				arr,
				left_bound_second,
				right_bound_second,
				arr[middle_index_first]
			);

			middle_indexes[i * 2] = middle_index_first;
			middle_indexes[i * 2 + 1] = middle_index_second;
		}

		#pragma omp parallel for schedule(static,1)
		for (int i = 0; i < array_pairs_num * 2; i++) {
			const bool merge_first_parts_of_pair = i % 2 == 0;
			const int left_bound_first = merge_first_parts_of_pair
				? boundaries[i * 2]
				: middle_indexes[i - 1];
			const int right_bound_first = merge_first_parts_of_pair
				? middle_indexes[i]
				: boundaries[i * 2 - 1];
			const int left_bound_second = merge_first_parts_of_pair
				? boundaries[(i + 1) * 2]
				: middle_indexes[i];
			const int right_bound_second = merge_first_parts_of_pair
				? middle_indexes[i + 1]
				: boundaries[i * 2 + 1];

			DacMerge(
				arr, arr_temp, i, boundaries,
				left_bound_first, right_bound_first, left_bound_second, right_bound_second
			);
		}

		for (int i = 0; i < arr_size; i++) {
			arr[i] = arr_temp[i];
		}

		array_pairs_num /= 2;

		// We must fix pairs boundaries
		if (array_pairs_num != 0) {
			for (int i = 0; i < array_pairs_num; i++) {
				boundaries[i * 4] = boundaries[i * 8];
				boundaries[i * 4 + 1] = boundaries[i * 8 + 1];
				boundaries[i * 4 + 2] = boundaries[i * 8 + 2];
				boundaries[i * 4 + 3] = boundaries[i * 8 + 3];
			}
		}
	} // while (array_pairs_num != 0)

	delete[] boundaries;
	delete[] arr_temp;
	delete[] middle_indexes;
}
