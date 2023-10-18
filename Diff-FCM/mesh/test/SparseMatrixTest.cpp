#include "mesh/SparseMatrix.h"

#include <gtest/gtest.h>

TEST(SparseMatrixTest, SparseCtor)
{
    SparseMatrix matrix(10);

    matrix(0,0) += 1.0;
    matrix(9,9) += 1.0;

    for (int i = 1; i < 9; ++i)
    {
        matrix(i, i-1) += -1.0;
        matrix(i, i) += 2.0;
        matrix(i, i+1) += -1.0;
    }

    matrix.assemble();

    matrix(0,0) = 10.0;

    EXPECT_DOUBLE_EQ(matrix(0,0), 10.0);
    EXPECT_DOUBLE_EQ(matrix(9,9), 1.0);
    EXPECT_EQ(matrix.nonZeros(), 26);
}

TEST(SparseMatrixTest, SparseSolve)
{
    SparseMatrix matrix(11);

    matrix(0,0) += 1.0;
    matrix(10,10) += 1.0;

    for (int i = 1; i < 10; ++i)
    {
        matrix(i, i-1) += -1.0;
        matrix(i, i) += 2.0;
        matrix(i, i+1) += -1.0;
    }

    matrix.assemble();

    std::vector<double> b(11, 0.0);
    b[0] = 1.0;
    b[10] = 0.0;

    std::vector<double> x = solve(matrix, b);

    EXPECT_DOUBLE_EQ(x[0], 1.0);
    EXPECT_DOUBLE_EQ(x[5], 0.5);
    EXPECT_DOUBLE_EQ(x[10], 0.0);
}
