#include "basis/Bspline.h"

#include <gtest/gtest.h>
#include <iostream>

#include "types/simd.h"

TEST(BSplineTest, BSpline2DBasis1stOrderTest){

    BSplineBasis<1, double> basisFunctions;
    BSpline<1, double> bSpline;
    constexpr int Size = BSpline<1,double>::size();

    double x = 0.5;
    double y = -0.5;

    auto basisFunction = basisFunctions.begin();

    for (int j = 0; j < Size; ++j)
    {
        for (int i = 0; i < Size; ++i)
        {
            EXPECT_DOUBLE_EQ(basisFunction.eval(x,y), bSpline(i,x)*bSpline(j,y));
            ++basisFunction;
        }
    }

    EXPECT_TRUE(!(basisFunction != basisFunctions.end()));
}

TEST(BSplineTest, BSpline2DBasis4thOrderTest){

    BSplineBasis<4, double> basisFunctions;
    BSpline<4, double> bSpline;
    constexpr int Size = BSpline<4,double>::size();

    double x = 0.5;
    double y = -0.5;

    auto basisFunction = basisFunctions.begin();

    for (int j = 0; j < Size; ++j)
    {
        for (int i = 0; i < Size; ++i)
        {
            EXPECT_DOUBLE_EQ(basisFunction.eval(x,y), bSpline(i,x)*bSpline(j,y));
            ++basisFunction;
        }
    }

    EXPECT_TRUE(!(basisFunction != basisFunctions.end()));
}

TEST(BSplineTest, BasisFourthOrderTwoDimensionNodeModes) { 

    Basis<BSpline<4, double>, Topology::Nodes, 2> basisFunctions;
    BSpline<4, double> bSpline;
    constexpr int Size = BSpline<4,double>::size();

    double x = 0.5;
    double y = -0.5;

    auto basisFunction = basisFunctions.begin();

    EXPECT_DOUBLE_EQ(basisFunction.eval(x,y), bSpline(0,x)*bSpline(0,y));
    ++basisFunction;
    EXPECT_DOUBLE_EQ(basisFunction.eval(x,y), bSpline(Size-1,x)*bSpline(0,y));
    ++basisFunction;
    EXPECT_DOUBLE_EQ(basisFunction.eval(x,y), bSpline(0,x)*bSpline(Size-1,y));
    ++basisFunction;
    EXPECT_DOUBLE_EQ(basisFunction.eval(x,y), bSpline(Size-1,x)*bSpline(Size-1,y));
    ++basisFunction;

    EXPECT_TRUE(!(basisFunction != basisFunctions.end()));
}

TEST(BSplineTest, BSpline3DBasis1stOrderTest){

    Basis<BSpline<1, double>, Topology::Cell, 3> basisFunctions;
    BSpline<1, double> bSpline;
    constexpr int Size = BSpline<1,double>::size();

    double x = 0.5;
    double y = -0.5;
    double z = 0.5;

    auto basisFunction = basisFunctions.begin();

    for (int k = 0; k < Size; ++k)
        for (int j = 0; j < Size; ++j)
            for (int i = 0; i < Size; ++i)
            {
                EXPECT_DOUBLE_EQ(basisFunction.eval(x,y,z), bSpline(i,x)*bSpline(j,y)*bSpline(k,z));
                ++basisFunction;
            }   

    EXPECT_TRUE(!(basisFunction != basisFunctions.end()));
}

TEST(BSplineTest, BSpline3DBasis4thOrderTest){

    Basis<BSpline<4, double>, Topology::Cell, 3> basisFunctions;
    BSpline<4, double> bSpline;
    constexpr int Size = BSpline<4,double>::size();

    double x = 0.5;
    double y = -0.5;
    double z = 0.5;

    auto basisFunction = basisFunctions.begin();

    for (int k = 0; k < Size; ++k)
        for (int j = 0; j < Size; ++j)
            for (int i = 0; i < Size; ++i)
            {
                EXPECT_DOUBLE_EQ(basisFunction.eval(x,y,z), bSpline(i,x)*bSpline(j,y)*bSpline(k,z));
                ++basisFunction;
            }   

    EXPECT_TRUE(!(basisFunction != basisFunctions.end()));
}


TEST(BSplineTest, BasisFourthOrderThreeDimensionNodeModes) { 

    Basis<BSpline<4, double>, Topology::Nodes, 3> basisFunctions;
    BSpline<4, double> bSpline;
    constexpr int Size = BSpline<4,double>::size();

    double x = 0.5;
    double y = -0.5;
    double z = 0.5;

    auto basisFunction = basisFunctions.begin();

    EXPECT_DOUBLE_EQ(basisFunction.eval(x,y,z), bSpline(0,x)*bSpline(0,y)*bSpline(0,z));
    ++basisFunction;
    EXPECT_DOUBLE_EQ(basisFunction.eval(x,y,z), bSpline(Size-1,x)*bSpline(0,y)*bSpline(0,z));
    ++basisFunction;
    EXPECT_DOUBLE_EQ(basisFunction.eval(x,y,z), bSpline(0,x)*bSpline(Size-1,y)*bSpline(0,z));
    ++basisFunction;
    EXPECT_DOUBLE_EQ(basisFunction.eval(x,y,z), bSpline(Size-1,x)*bSpline(Size-1,y)*bSpline(0,z));
    ++basisFunction;
    EXPECT_DOUBLE_EQ(basisFunction.eval(x,y,z), bSpline(0,x)*bSpline(0,y)*bSpline(Size-1,z));
    ++basisFunction;
    EXPECT_DOUBLE_EQ(basisFunction.eval(x,y,z), bSpline(Size-1,x)*bSpline(0,y)*bSpline(Size-1,z));
    ++basisFunction;
    EXPECT_DOUBLE_EQ(basisFunction.eval(x,y,z), bSpline(0,x)*bSpline(Size-1,y)*bSpline(Size-1,z));
    ++basisFunction;
    EXPECT_DOUBLE_EQ(basisFunction.eval(x,y,z), bSpline(Size-1,x)*bSpline(Size-1,y)*bSpline(Size-1,z));
    ++basisFunction;

    EXPECT_TRUE(!(basisFunction != basisFunctions.end()));
}