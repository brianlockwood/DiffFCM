#include "basis/Bspline.h"

#include <gtest/gtest.h>
#include <iostream>

#include "types/simd.h"

TEST(BSplineTest, BSpline1stOrderTest){

    BSpline<1, double> bspline;

    EXPECT_DOUBLE_EQ(bspline(0, -1.0), 1.0);
    EXPECT_DOUBLE_EQ(bspline(0, 1.0), 0.0);

    EXPECT_DOUBLE_EQ(bspline(1, -1.0), 0.0);
    EXPECT_DOUBLE_EQ(bspline(1, 1.0), 1.0);
}

TEST(BSplineTest, BSpline2ndOrderTest){

    BSpline<2, double> bspline;

    EXPECT_DOUBLE_EQ(bspline(0, -1.0), 1.0);
    EXPECT_DOUBLE_EQ(bspline(0, 1.0), 0.0);

    EXPECT_DOUBLE_EQ(bspline(1, -1.0), 0.0);
    EXPECT_DOUBLE_EQ(bspline(1, 0.0), 0.5);
    EXPECT_DOUBLE_EQ(bspline(1, 1.0), 0.0);

    EXPECT_DOUBLE_EQ(bspline(2, -1.0), 0.0);
    EXPECT_DOUBLE_EQ(bspline(2, 1.0), 1.0);
}

