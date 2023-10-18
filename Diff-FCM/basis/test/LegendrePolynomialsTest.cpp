#include "basis/LegendrePolynomials.h"

#include <gtest/gtest.h>
#include <iostream>

#include "types/simd.h"

TEST(LegendrePolynomials, DoubleTest){
    double value = LegendrePolynomial<0, double>::eval(-1.0);
    EXPECT_DOUBLE_EQ(value, 1.0);

    value = LegendrePolynomial<0, double>::eval(1.0);
    EXPECT_DOUBLE_EQ(value, 1.0);

    value = LegendrePolynomial<1, double>::eval(-1.0);
    EXPECT_DOUBLE_EQ(value, -1.0);

    value = LegendrePolynomial<1, double>::eval(1.0);
    EXPECT_DOUBLE_EQ(value, 1.0);
}

#ifdef SSE2
TEST(LegendrePolynomials, SSETest){
    double values[2];

    values[0] = LegendrePolynomial<0, double>::eval(-1.0);
    values[1] = LegendrePolynomial<0, double>::eval(1.0);

    v2d x{-1.0, 1.0};
    v2d result = LegendrePolynomial<0, v2d>::eval(x);

    auto resultArray = result.asArray();
    EXPECT_DOUBLE_EQ(resultArray[0], values[0]);
    EXPECT_DOUBLE_EQ(resultArray[1], values[1]);
}
#elif AVX
TEST(LegendrePolynomials, AVX2Test){
    double values[4];

    values[0] = LegendrePolynomial<0, double>::eval(-1.0);
    values[1] = LegendrePolynomial<0, double>::eval(1.0);
    values[2] = LegendrePolynomial<0, double>::eval(-0.5);
    values[3] = LegendrePolynomial<0, double>::eval(0.5);

    v4d x{-1.0, 1.0, -0.5, 0.5};
    v4d result = LegendrePolynomial<0, v4d>::eval(x);

    auto resultArray = result.asArray();
    EXPECT_DOUBLE_EQ(resultArray[0], values[0]);
    EXPECT_DOUBLE_EQ(resultArray[1], values[1]);
    EXPECT_DOUBLE_EQ(resultArray[2], values[2]);
    EXPECT_DOUBLE_EQ(resultArray[3], values[3]);
}
#endif

// int main(int argc, char** argv)
// {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }