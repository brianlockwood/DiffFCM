#include "mesh/Grid.h"
#include "mesh/DOF.h"

#include <gtest/gtest.h>

#include <iostream>

TEST(MeshStorageTest, GridStorage)
{
    Grid<2> grid(5, 5);

    grid.setBounds({0.0, 0.0}, {1.0, 1.0});

    auto nodeStorage = GridStorage<2,int>(grid.getNx(), grid.getNy());

    GridLoops::nodeLoop(grid, [&](int i, int j) {
        nodeStorage(i,j) = i*10 + j*5;
    });


    GridLoops::nodeLoop(grid, [&](int i, int j) {
        int value = i*10 + j*5;

        EXPECT_EQ( nodeStorage(i,j), value);
    });
}


TEST(MeshStorageTest, GridRaggedArray)
{
    Grid<2> grid(2, 2);

    grid.setBounds({0.0, 0.0}, {1.0, 1.0});

    auto cellOrder = GridStorage<2, int>(grid.getNx()-1, grid.getNy()-1);

    GridLoops::cellLoop(grid, [&](int i, int j) {
        cellOrder(i,j) = 3;
    });

    auto [cellDofs, totalDofs] = labelDegreesOfFreedom(grid, cellOrder);

    EXPECT_EQ(cellDofs(0,0)[0], 0);
    EXPECT_EQ(cellDofs(0,0)[4], 4);
    EXPECT_EQ(cellDofs(0,0)[8], 8);
}