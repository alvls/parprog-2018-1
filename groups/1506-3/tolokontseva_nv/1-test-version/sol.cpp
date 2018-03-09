#include <list>

/*
#define BITES_IN_DIGETS 4 //number of bites in one radix
#define DIGITS_VALUES 16 // number of possible values of 1 digit. 1 digit = 4 bit => 2^4 values
*/

#define BITES_IN_DIGETS 8
#define DIGITS_VALUES 256

#define MAX_DIGITS_COUNT (64 / BITES_IN_DIGETS) //64 bites / 8 bit = 8
#define MASK (DIGITS_VALUES - 1) //11111111

typedef unsigned int un_int; /*for diget*/
typedef unsigned long long int ulong; /* 8 bytes as well as in double */

un_int get_digit(double num, size_t offset);
void merge_lists(double *res, std::list<double> *arr_list, int size);
void process_number(std::list<double> *arr_of_lists, double number,  int digit_num);

/* sorts given array. This function does not change initial array.
 Input:
	* arr - pointer to array of double
	* res - array to keep the result
	* size - number of elements in array
	*/
void radix_sort(double *arr, double* res, int size) {
	std::memcpy((void*)res, (void*)arr, sizeof(double)*size); // copy initial arr to res

	std::list<double> sort_help_arr[DIGITS_VALUES]; //pockets
	//i is diget number (0 from the right, 1 from the right, etc)
	for (int i = 0; i < MAX_DIGITS_COUNT; i++) {
		for (int cur_num = 0; cur_num < size; cur_num++) {
			process_number(sort_help_arr, res[cur_num], i);
		}
		merge_lists(res, sort_help_arr, DIGITS_VALUES);
	}
	
	//at this step all numbers are sorted, but first bit (with sign) is not correctly handled, so this should be fixed
	for (int i = 0; i < size; i++) {
		if (res[i] < 0) {
			sort_help_arr[0].push_front(res[i]);
		}
		else if (res[i] > 0) {
			sort_help_arr[1].push_back(res[i]);
		}
		else { 
			//there go +0.0 and -0.0
			// -0.0 is special case: its first bit is 1, so it's always is considered 'bigger' than any positive number
			sort_help_arr[1].push_front(res[i]);
		}
	}
	merge_lists(res, sort_help_arr, 2);
}

/* one "digit" is BITES_IN_DIGETS bits. Count from right. E.g. if BITES_IN_DIGETS is 4:
* 0000 0001 0011 0101 1001 0001
* zero digit is 0001, second is 0101 and so on.
*/
un_int get_digit(double d, size_t offset) {
	//size of ulong is the same as size of double (8 bytes)
	ulong n;
	//I do this because bite operations can be applied only to ~int
	std::memcpy(&n, &d, sizeof d);
	//move everything to the right to place target 4 bites in the end
	n >>= offset * BITES_IN_DIGETS;
	// apply mask 00...01111, so everything except last 4 bites became zero
	n &= MASK;
	return (un_int)n;
}

/*
  Function is used inside sort to merge lists into one array
*/
//I can try to improve it: add check of order and if it's already OK then stop sorting
//Not sure how much it will increase time so need to check
void merge_lists(double *res, std::list<double> *arr_list, int size) {
	int k = 0; //index in result
	for (int i = 0; i < size; i++) {
		while (!arr_list[i].empty())
		{
			res[k] = arr_list[i].front();
			arr_list[i].pop_front();
			k++;
		}
	}
	return;
}

/*
	Function puts the number to one of lists from the list array depending on value of digit_num-th digit
*/
void process_number(std::list<double> *arr_of_lists, double number, int digit_num) {
	un_int digit = get_digit(number, digit_num);
	arr_of_lists[digit].push_back(number);
	return;
};
