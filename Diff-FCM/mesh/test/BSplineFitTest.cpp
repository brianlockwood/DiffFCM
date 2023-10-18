#include "mesh/SparseMatrix.h"
#include "basis/Bspline.h"

#include <gtest/gtest.h>

void function(double x)
{
    constexpr double pi = 4.0*std::atan(1.0);
    return std::sin(2*pi*x);
}

TEST(BSplineFitTest, TestFit)
{
    int N = 10;
    constexpr int p = 2;

    double L = 1.0;

    

}

