#include "basis/LegendreBasis.h"

#include <gtest/gtest.h>
#include <iostream>

#include "types/simd.h"

TEST(LegendreBasis1DTest, BasisEvalTest){
    double value = LegendreBasis1D<double>::eval<0>(-1.0);
    EXPECT_DOUBLE_EQ(value, 1.0);

    value = LegendreBasis1D<double>::eval<0>(1.0);
    EXPECT_DOUBLE_EQ(value, 0.0);

    value = LegendreBasis1D<double>::eval<0>(0.0);
    EXPECT_DOUBLE_EQ(value, 0.5);

    value = LegendreBasis1D<double>::eval<1>(-1.0);
    EXPECT_DOUBLE_EQ(value, 0.0);

    value = LegendreBasis1D<double>::eval<1>(1.0);
    EXPECT_DOUBLE_EQ(value, 1.0);

    value = LegendreBasis1D<double>::eval<1>(0.0);
    EXPECT_DOUBLE_EQ(value, 0.5);

    value = LegendreBasis1D<double>::eval<2>(1.0);
    EXPECT_DOUBLE_EQ(value, 0.0);

    value = LegendreBasis1D<double>::eval<2>(-1.0);
    EXPECT_DOUBLE_EQ(value, 0.0);

    value = LegendreBasis1D<double>::eval<2>(0.0);
    EXPECT_NEAR(value, -0.612372435695795, 1e-12);
}


#ifdef SSE2
template <int Order>
void checkSSE2Consistency()
{
    double values[2];

    values[0] = LegendreBasis1D<double>::eval<Order>(-1.0);
    values[1] = LegendreBasis1D<double>::eval<Order>(1.0);

    v2d x{-1.0, 1.0};
    v2d result = LegendreBasis1D<v2d>::eval<Order>(x);

    auto resultArray = result.asArray();

    EXPECT_DOUBLE_EQ(resultArray[0], values[0]);
    EXPECT_DOUBLE_EQ(resultArray[1], values[1]);

    values[0] = LegendreBasis1D<double>::eval<Order>(0.0);

    x = v2d{0.0, 0.0};
    result = LegendreBasis1D<v2d>::eval<Order>(x);

    resultArray = result.asArray();
    EXPECT_DOUBLE_EQ(resultArray[0], values[0]);
}


TEST(LegendreBasis1DTest, SSETest){
    checkSSE2Consistency<0>();
    checkSSE2Consistency<1>();
    checkSSE2Consistency<2>();
}
#elif AVX
template <int Order>
void checkSSE2Consistency()
{
    double values[3];

    values[0] = LegendrePolynomial<0, double>::eval(-1.0);
    values[1] = LegendrePolynomial<0, double>::eval(1.0);
    values[2] = LegendrePolynomial<0, double>::eval(0.0);

    v4d x{-1.0, 1.0, 0.0, 0.0};
    v4d result = LegendrePolynomial<0, v4d>::eval(x);

    auto resultArray = result.asArray();
    EXPECT_DOUBLE_EQ(resultArray[0], values[0]);
    EXPECT_DOUBLE_EQ(resultArray[1], values[1]);
    EXPECT_DOUBLE_EQ(resultArray[2], values[2]);
}

TEST(LegendreBasis1DTest, AVX2Test){
    checkSSE2Consistency<0>();
    checkSSE2Consistency<1>();
    checkSSE2Consistency<2>();
}
#endif
