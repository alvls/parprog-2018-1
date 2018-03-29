#define _CRT_SECURE_NO_WARNINGS

#include "sol.h"
//if element is not found return value of the element which is "closer" to it
int binary_search(double* arr, int size, double value) {
	if (value < arr[0]) {
		return 0;
	}
	int l = 0, //left border index
		r = size - 1, //right border index
		m; //middle element index
	double tmp_val;
	while (l <= r) {
		m = (l + r) / 2;
		tmp_val = arr[m];
		if (tmp_val > value) {
			r = m - 1;
		}
		else if (tmp_val < value)
		{
			l = m + 1;
		}
		else
		{
			return m;
		}
	}
	return l;
}

//simple merge of 2 sorted arrays done by one thread. 
//res should be pointer to array with size size1+size2
void merge(double *arr1, double *arr2, double *res, int size1, int size2) {
	int f_ind = 0, s_ind = 0, res_ind = 0;//first array index, second array index

	while (f_ind < size1)
	{
		while (arr2[s_ind] < arr1[f_ind] && s_ind < size2) {
			res[res_ind++] = arr2[s_ind++];
		}
		res[res_ind++] = arr1[f_ind++];
	}
	while (s_ind < size2)
	{
		res[res_ind++] = arr2[s_ind++];
	}
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
void merge_lists(double *res, std::list<double> *arr_list, int size, int digit_num) {
	int k = 0; //index in result
	if (digit_num != MAX_DIGITS_COUNT - 1)
	{
		for (int i = 0; i < size; i++) {
			while (!arr_list[i].empty())
			{
				res[k] = arr_list[i].front();
				arr_list[i].pop_front();
				k++;
			}
		}
	}
	else {
		for (int i = size - 1; i >= size / 2; i--)
		{
			while (!arr_list[i].empty())
			{
				//or back?
				res[k] = arr_list[i].back();
				arr_list[i].pop_back();
				k++;
			}
		}
		for (int i = 0; i < size / 2; i++)
		{
			while (!arr_list[i].empty())
			{
				res[k] = arr_list[i].front();
				arr_list[i].pop_front();
				k++;
			}
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

class merge_node
{
private:
	//merge 2 arrays by threads_nums threads
	int threads_nums;
	int **part_size, size_arr[2];
	double **res_arr, *arr_arr[2], ***start_p;
	void _merge_node(int threads_num) {
		this->threads_nums = threads_num;
		part_size = new int*[threads_num];
		start_p = new double**[threads_num];
		res_arr = new double*[threads_num];
		for (int i = 0; i < threads_num; i++) {
			//for 2 pointers: start in 1st array, start in second array
			start_p[i] = new double*[2];
			part_size[i] = new int[2];
			res_arr[i] = NULL;
		}
	}
	void _destr() {
		for (int i = 0; i < threads_nums; i++) {
			delete[]start_p[i];
			delete[] part_size[i];
			if (res_arr[i] != NULL) {
				delete[] res_arr[i];
			}
		}
		delete[] res_arr;
		delete[] part_size;
		delete[] start_p;
	}
	void count_indexes() {
		//ind_arr[0] is index of X in the first array, ind_arr[1] is index of X in the second array,
		//ind_arr[2] is index of Y in the first array, ind_arr[3] is index of Y in the second array,
		//and so on
		int odd = 0,
			even = 1,
			shift1 = 0,
			shift2 = 0,
			i, ind_even, ind_odd;

		for (i = 0; i < threads_nums - 1; i++)
		{
			even = i * 2;
			odd = even + 1;
			ind_even = size_arr[0] * (i + 1) / threads_nums;
			//STL's binary search return only if value is present :(
			//my binary_search can return -1, but in this case everything should work too (size = -1)	
			ind_odd = binary_search(arr_arr[1], size_arr[1], arr_arr[0][ind_even]);
			start_p[i][0] = arr_arr[0] + shift1;
			start_p[i][1] = arr_arr[1] + shift2;
			part_size[i][0] = ind_even - shift1;
			part_size[i][1] = ind_odd - shift2;
			if (part_size[i][1] < 0)
			{
				part_size[i][1] = 0;
			}
			shift2 = ind_odd;
			shift1 = ind_even;
		}
		start_p[i][0] = arr_arr[0] + shift1;
		start_p[i][1] = arr_arr[1] + shift2;
		part_size[i][0] = size_arr[0] - ind_even;
		part_size[i][1] = size_arr[1] - ind_odd;
		if (shift2 == 0)
		{
			part_size[i][1] = 0;
		}
	}
public:
	merge_node()
	{
		threads_nums = 2;
	}

	~merge_node()
	{
		_destr();

	};
	void initialize(double* arr1, double *arr2, int size1, int size2, int threads_num) {
		threads_nums = threads_num;
		_merge_node(threads_nums);
		arr_arr[0] = arr1;
		arr_arr[1] = arr2;
		size_arr[0] = size1;
		size_arr[1] = size2;
		count_indexes();
	}
	void merge_subarr(int i) {
		int size = part_size[i][0] + part_size[i][1];
		if (size > 0) {
			res_arr[i] = new double[size];
			merge(start_p[i][0], start_p[i][1], res_arr[i], part_size[i][0], part_size[i][1]);
		}
	}
	void join_res(double* res) {
		int size;
		for (int i = 0; i < threads_nums; i++) {
			size = part_size[i][0] + part_size[i][1];
			for (int j = 0; j < size; j++) {
				res[j] = res_arr[i][j];
			}
			res += size;
		}
	}
	int get_final_size() {
		return size_arr[0] + size_arr[1];
	}
};


/* sorts given array. This function does not change initial array.
Input:
* arr - pointer to array of double
* res - array to keep the result
* size - number of elements in array
* threads_num - number of threads that should be used to sort
*/
void radix_sort_openmp(double *arr, double* res, int size, int threads_num) {
	omp_set_num_threads(threads_num);
	memcpy((void*)res, (void*)arr,sizeof(double)*size);
	int chunks_num = threads_num;
	if (threads_num == 2 || threads_num == 4) {
		chunks_num *= threads_num;
	}
	/*** for the final merges***/
	int merge_times = chunks_num / 2; //keeps number of arrays that should be merged at current step
	merge_node *merge_struct; //keeps all the indexes and trasitive results of merges and so on
#pragma omp parallel firstprivate(res,size,threads_num,chunks_num) shared(merge_struct, merge_times)
	{
		std::list<double> sort_help_arr[DIGITS_VALUES]; //buckets
		double *ptr; //pointer to start of subarray
		int *part_sizes; //array for part sizes, used only by master
		int thread_num = omp_get_thread_num(), //thread number
			part_size;
#pragma omp for schedule(dynamic)
		for (int chunkId = 0; chunkId < chunks_num; chunkId++) {
			part_size = size / chunks_num; //size of subarray that thread should sort
			ptr = res + chunkId*part_size; //pointer to start of subarray

			if (chunkId == chunks_num - 1)
			{
				part_size += size%chunks_num;
			}

			//sort pieces of arrs
			for (int i = 0; i < MAX_DIGITS_COUNT; i++) {
				for (int j = 0; j < part_size; j++) {
					process_number(sort_help_arr, ptr[j], i);
				}
				merge_lists(ptr, sort_help_arr, DIGITS_VALUES, i);
			}
		}
		//wait until everyone finish sorting
#pragma omp barrier

		/*merge sorted subarrays*/
#pragma omp master 
		{
			part_sizes = new int[chunks_num]; //there are kept sizes of subarrays that sorts each thread
			for (int i = 0; i < chunks_num; i++) {
				part_sizes[i] = size / chunks_num;
			}
			part_sizes[chunks_num - 1] += size%chunks_num;
		}
		while (merge_times != 0) {
#pragma omp master 
			{
				int shift = 0, i, j, threads_per_arr = chunks_num / merge_times;
				merge_struct = new merge_node[merge_times];
				for (i = 0, j = 0; j < merge_times; i += 2, j++)
				{
					//count indexes
					merge_struct[j].initialize(res + shift, res + shift + part_sizes[i],
						part_sizes[i], part_sizes[i + 1], threads_per_arr);
					shift += part_sizes[i] + part_sizes[i + 1];
				}
			}
			//wait for master to finish
#pragma omp barrier

			/*merge parallely*/
			for (int j = 0; j < merge_times; j++)
			{
#pragma omp for schedule(dynamic) nowait
				for (int i = 0; i < chunks_num / merge_times; i++) {
					merge_struct[j].merge_subarr(i);
				}
			}
			//wait for all merges to finish
#pragma omp barrier
			//join the result via master
#pragma omp master 
			{
				double *res_p = res;
				for (int i = 0; i < merge_times; i++)
				{
					merge_struct[i].join_res(res_p);
					part_sizes[i] = merge_struct[i].get_final_size();
					res_p += part_sizes[i];
				}
				merge_times /= 2;

				delete[] merge_struct;
			}

#pragma omp barrier
		}
#pragma omp master 
		{
			delete[] part_sizes; 
		}
	}
}
