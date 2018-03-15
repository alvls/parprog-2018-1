#include <gtest.h>
#include "Grehem.h"

TEST(Grehem, can_find_min_element)
{
	dot* arr = new dot[3];
	arr[0].x = 6;
	arr[0].y = 5;
	arr[1].x = 1;
	arr[1].y = 3;
	arr[2].x = 4;
	arr[2].y = 3;
	dot result;
	result.x = 1;
	result.y = 3;
	searchMinElement(arr, 3);


	EXPECT_EQ(result, arr[0]);
}

TEST(Grehem, quick_sort_works_correctly)
{
	dot* arr = new dot[4];
	arr[0].x = 0;
	arr[0].y = 0;
	arr[1].x = 5;
	arr[1].y = 4;
	arr[2].x = 0;
	arr[2].y = 3;
	arr[3].x = 9;
	arr[3].y = 10;
	bool check = true;
	dot* arr2 = new dot[4];
	arr2[0].x = 0;
	arr2[0].y = 0;
	arr2[1].x = 5;
	arr2[1].y = 4;
	arr2[2].x = 9;
	arr2[2].y = 10;
	arr2[3].x = 0;
	arr2[3].y = 3;
	quickSort(arr, 1, 4);
	for (auto i = 0; i < 4; i++)
	{
		if ((arr[i].x != arr2[i].x) || (arr[i].y != arr2[i].y))
		{
			check = false;
		}
	}

	EXPECT_EQ(1, check);
}

TEST(Grehem,grehem_works_correctly)
{
	dot* arr = new dot[4];
	arr[0].x = 0;
	arr[0].y = 0;
	arr[1].x = 9;
	arr[1].y = 10;
	arr[2].x = 0;
	arr[2].y = 3;
	arr[3].x = 5;
	arr[3].y = 4;
	bool check = true;
	dot* result = new dot[4];
	result[0].x = 0;
	result[0].y = 0;
	result[1].x = 9;
	result[1].y = 10;
	result[2].x = 0;
	result[2].y = 3;
	result[3].x = 0;
	result[3].y = 0;
	std::pair<dot*,int> answer = grehemMethod(arr, 4);

	for (auto i = 0; i < answer.second; i++)
	{
		if ((answer.first[i].x != result[i].x) || (answer.first[i].y != result[i].y))
		{
			check = false;
		}
	}

	EXPECT_EQ(1, check);
}