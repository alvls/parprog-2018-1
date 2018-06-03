#pragma once
#include <list>
#include <omp.h>

#define BITES_IN_DIGETS 8
#define DIGITS_VALUES 256

#define MAX_DIGITS_COUNT (64 / BITES_IN_DIGETS) //64 bites / 8 bit = 8
#define MASK (DIGITS_VALUES - 1) //11111111

typedef unsigned int un_int; /*for diget*/
typedef unsigned long long int ulong; /* 8 bytes as well as in double */

un_int get_digit(double num, size_t offset);
void merge_lists(double *res, std::list<double> *arr_list, int size, int digit_num);
void process_number(std::list<double> *arr_of_lists, double number, int digit_num);

void radix_sort_openmp(double *arr, double* res, int size, int proc_num);