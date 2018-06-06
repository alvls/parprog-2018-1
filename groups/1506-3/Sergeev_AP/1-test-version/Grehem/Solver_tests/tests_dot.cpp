#include <gtest.h>
#include "Dot.h"

TEST(Dot, comparison_works_correctly)
{
	dot dot1;
	dot1.x = 1;
	dot1.y = 1;
	dot dot2;
	dot2.x = 2;
	dot2.y = 3;

	EXPECT_EQ(1, dot1 < dot2);
}

TEST(Dot, equal_points_are_equal)
{
	dot dot1;
	dot1.x = 4;
	dot1.y = 1;
	dot dot2;
	dot2.x = 4;
	dot2.y = 1;

	EXPECT_EQ(1, dot1 == dot2);
}

TEST(Dot, addition_works_correctly)
{
	dot dot1;
	dot1.x = 1;
	dot1.y = 1;
	dot dot2;
	dot2.x = 2;
	dot2.y = 3;
	dot dotPlus;
	dotPlus.x = 1;
	dotPlus.y = 2;

	EXPECT_EQ(1, dot2 == dot1 + dotPlus);
}

TEST(Dot, subtraction_works_correctly)
{
	dot dot1;
	dot1.x = 1;
	dot1.y = 1;
	dot dot2;
	dot2.x = 2;
	dot2.y = 3;
	dot dotMinus;
	dotMinus.x = 1;
	dotMinus.y = 2;

	EXPECT_EQ(1, dot1 == dot2 - dotMinus);
}