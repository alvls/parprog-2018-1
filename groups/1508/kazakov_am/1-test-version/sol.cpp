unsigned char GetByte(const double* number, const unsigned digit_num) {
	return (reinterpret_cast<const unsigned char*>(number))[digit_num];
}

void LsdRadixSort(double* arr, const size_t arr_size) {
	const int kDigitsNumber = 8;
	const size_t kDigitPossibleValuesNumber = 256;
	const size_t kDigitPossibleValuesNumberHalf = kDigitPossibleValuesNumber >> 1;

	int* counters = new int[kDigitPossibleValuesNumber];
	double* arr_temp = new double[arr_size];

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
	delete[] arr_temp;
}