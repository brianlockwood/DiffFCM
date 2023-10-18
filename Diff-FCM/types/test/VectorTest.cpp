#include "types/Vector.h"

#include <gtest/gtest.h>


TEST(VectorTest, Assignment)
{
    Vector<double, 3> a;

    a(0) = 1.0;
    a(1) = 2.0;
    a(2) = 3.0;

    EXPECT_DOUBLE_EQ(a(0),1.0);
    EXPECT_DOUBLE_EQ(a(1),2.0);
    EXPECT_DOUBLE_EQ(a(2),3.0);
}