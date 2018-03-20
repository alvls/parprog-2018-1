#include "../gtest/gtest/gtest.h"
#include "../../include/complex_numbers.h"
TEST(complex, can_add)
{
    Complex q1(1, 2), q2(2, 4);
    EXPECT_TRUE(q1+q1 == q2);
}
TEST(complex, can_conjugate)
{
    Complex q1(1, 2), q2(1, -2);
    EXPECT_TRUE(q1 == q2.getConjugate());
}
TEST(complex, can_mult)
{
    Complex q1(3, 2), q2(13,0);
    EXPECT_TRUE(q1*q1.getConjugate() == q2);
}