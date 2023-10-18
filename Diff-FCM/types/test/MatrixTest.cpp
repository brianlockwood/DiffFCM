#include "types/Matrix.h"

#include <gtest/gtest.h>


TEST(MatrixTest, Assignment)
{
    Matrix<double, 3> a;

    a(0,0) = 1.0;
    a(0,1) = 2.0;
    a(0,2) = 3.0;
    a(1,0) = 4.0;
    a(1,1) = 5.0;
    a(1,2) = 6.0;
    a(2,0) = 7.0;
    a(2,1) = 8.0;
    a(2,2) = 9.0;

    EXPECT_DOUBLE_EQ(a(0,0), 1.0);
    EXPECT_DOUBLE_EQ(a(0,1), 2.0);
    EXPECT_DOUBLE_EQ(a(0,2), 3.0);

    EXPECT_DOUBLE_EQ(a(1,0), 4.0);
    EXPECT_DOUBLE_EQ(a(1,1), 5.0);
    EXPECT_DOUBLE_EQ(a(1,2), 6.0);

    EXPECT_DOUBLE_EQ(a(2,0), 7.0);
    EXPECT_DOUBLE_EQ(a(2,1), 8.0);
    EXPECT_DOUBLE_EQ(a(2,2), 9.0);
}