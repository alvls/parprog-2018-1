#include <gtest.h>
#include "Stack.h"

TEST(Stack, can_push_and_get)
{
	stack st(3);
	dot d1;
	d1.x = 1;
	d1.y = 2;
	st.push(d1);

	EXPECT_EQ(d1, st.get());
}

TEST(Stack, can_get_size_empty)
{
	stack st(3);

	EXPECT_EQ(0, st.getSize());
}

TEST(Stack, can_get_size_with_element)
{
	stack st(3);
	dot d1;
	d1.x = 1;
	d1.y = 2;
	st.push(d1);

	EXPECT_EQ(1, st.getSize());
}

TEST(Stack, can_push_and_pop)
{
	stack st(3);
	dot d1;
	d1.x = 1;
	d1.y = 2;
	st.push(d1);
	dot d2 = st.pop();

	EXPECT_EQ(d1, d2);
}

TEST(Stack, pop_element_is_deleted)
{
	stack st(3);
	dot d1;
	d1.x = 1;
	d1.y = 2;
	st.push(d1);
	dot d2 = st.pop();

	EXPECT_EQ(0, st.getSize());
}

TEST(Stack, can_get_array)
{
	stack st(3);
	dot d1;
	d1.x = 1;
	d1.y = 2;
	st.push(d1);
	dot d2;
	d2.x = 5;
	d2.y = 2;
	st.push(d2);
	bool check = false;
	dot* arr = new dot[2];
	arr = st.getArray();

	EXPECT_EQ(1, ((arr[0] == d1) && (arr[1] == d2)));
}