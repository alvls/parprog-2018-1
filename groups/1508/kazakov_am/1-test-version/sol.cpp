#include <iostream>

unsigned char GetByte(const double number, const unsigned digit_num) {
	const long long int_number = static_cast<long long>(number);

	return static_cast<unsigned char>(
		(int_number >> (8 * digit_num)) & 0xFF
	);
}

void LsdRadixSort(double* arr, const size_t arr_size) {
	const int kDigitsNumber = 8;
	const size_t kDigitPossibleValuesNumber = 256;

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

		for (size_t j = 0; j < arr_size; j++) {
			const unsigned char curr_digit_unsigned = GetByte(arr[j], i);
			const char curr_digit_signed = static_cast<char>(curr_digit_unsigned);
			const unsigned char counters_index = is_curr_digit_msd
				? curr_digit_signed + 128
				: curr_digit_unsigned;
			arr_temp[counters[counters_index]] = arr[j];
			counters[counters_index]++;
		}

		for (size_t j = 0; j < arr_size; j++) {
			arr[j] = arr_temp[j];
		}
	}

	delete[] counters;
	delete[] arr_temp;
}