#include <omp.h>
#include <vector>
#include <iostream>
using namespace std;

vector<double> merge(const vector<double>& left, const vector<double>& right)
{
	vector<double> result;
	unsigned left_it = 0, right_it = 0;

	while (left_it < left.size() && right_it < right.size())
	{
		if (left[left_it] < right[right_it])
		{
			result.push_back(left[left_it]);
			left_it++;
		}
		else
		{
			result.push_back(right[right_it]);
			right_it++;
		}
	}

	while (left_it < left.size())
	{
		result.push_back(left[left_it]);
		left_it++;
	}

	while (right_it < right.size())
	{
		result.push_back(right[right_it]);
		right_it++;
	}

	return result;
}

vector<double> mergesort(vector<double>& vec, int threads)
{
	if (vec.size() == 1)
	{
		return vec;
	}
	std::vector<double>::iterator middle = vec.begin() + (vec.size() / 2);

	vector<double> left(vec.begin(), middle);
	vector<double> right(middle, vec.end());

	if (threads > 1)
	{
#pragma omp parallel sections
		{
#pragma omp section
			{
				left = mergesort(left, threads / 2);
			}
#pragma omp section
			{
				right = mergesort(right, threads - threads / 2);
			}
		}
	}
	else
	{
		left = mergesort(left, 1);
		right = mergesort(right, 1);
	}
	return merge(left, right);
}