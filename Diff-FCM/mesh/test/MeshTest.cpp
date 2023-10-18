#include "mesh/Grid.h"
#include "mesh/Coord.h"

#include <gtest/gtest.h>

#include <iostream>

TEST(MeshTest, ThreeDGridCoords)
{
    Grid<3> grid(3, 3, 3);

    grid.setBounds({0.0, 0.0, 0.0}, {1.0, 1.0, 1.0});

    Coord<3> coords(grid);

    {
        Grid<3>::Point testPoint = coords(0,0,0);

        EXPECT_DOUBLE_EQ(testPoint[0], 0.0);
        EXPECT_DOUBLE_EQ(testPoint[1], 0.0);
        EXPECT_DOUBLE_EQ(testPoint[2], 0.0);
    }
    {
        Grid<3>::Point testPoint = coords(2,2,2);

        EXPECT_DOUBLE_EQ(testPoint[0], 1.0);
        EXPECT_DOUBLE_EQ(testPoint[1], 1.0);
        EXPECT_DOUBLE_EQ(testPoint[2], 1.0);
    }
    {
        Grid<3>::Point testPoint = coords(0,2,0);

        EXPECT_DOUBLE_EQ(testPoint[0], 0.0);
        EXPECT_DOUBLE_EQ(testPoint[1], 1.0);
        EXPECT_DOUBLE_EQ(testPoint[2], 0.0);
    }
    {
        Grid<3>::Point testPoint = coords(0,0,2);

        EXPECT_DOUBLE_EQ(testPoint[0], 0.0);
        EXPECT_DOUBLE_EQ(testPoint[1], 0.0);
        EXPECT_DOUBLE_EQ(testPoint[2], 1.0);
    }
    {
        Grid<3>::Point testPoint = coords(2,0,0);

        EXPECT_DOUBLE_EQ(testPoint[0], 1.0);
        EXPECT_DOUBLE_EQ(testPoint[1], 0.0);
        EXPECT_DOUBLE_EQ(testPoint[2], 0.0);
    }
    {
        Grid<3>::Point testPoint = coords(1,1,1);

        EXPECT_DOUBLE_EQ(testPoint[0], 0.5);
        EXPECT_DOUBLE_EQ(testPoint[1], 0.5);
        EXPECT_DOUBLE_EQ(testPoint[2], 0.5);
    }
}

TEST(MeshTest, TwoDGridCoords)
{
    Grid<2> grid(3, 3);

    grid.setBounds({0.0, 0.0}, {1.0, 1.0});

    Coord<2> coords(grid);

    {
        Grid<2>::Point testPoint = coords(0,0);

        EXPECT_DOUBLE_EQ(testPoint[0], 0.0);
        EXPECT_DOUBLE_EQ(testPoint[1], 0.0);
    }
    {
        Grid<2>::Point testPoint = coords(2,2);

        EXPECT_DOUBLE_EQ(testPoint[0], 1.0);
        EXPECT_DOUBLE_EQ(testPoint[1], 1.0);
    }
    {
        Grid<2>::Point testPoint = coords(0,2);

        EXPECT_DOUBLE_EQ(testPoint[0], 0.0);
        EXPECT_DOUBLE_EQ(testPoint[1], 1.0);
    }
    {
        Grid<2>::Point testPoint = coords(2,0);

        EXPECT_DOUBLE_EQ(testPoint[0], 1.0);
        EXPECT_DOUBLE_EQ(testPoint[1], 0.0);
    }
    {
        Grid<2>::Point testPoint = coords(1,1);

        EXPECT_DOUBLE_EQ(testPoint[0], 0.5);
        EXPECT_DOUBLE_EQ(testPoint[1], 0.5);
    }
}


// void printCellDetails(const Cell &cell)
// {
//     std::cout << "Cell Index for Cell" << cell.getIndex() << std::endl;
//     std::cout << "Nodes for Cell 0,0,0" << std::endl;
//     for (auto entity : cell.getNodes())
//     {
//         std::cout << entity << std::endl;
//     }
//     std::cout << "XEdges for Cell 0,0,0" << std::endl;
//     for (auto entity : cell.getXEdges())
//     {
//         std::cout << entity << std::endl;
//     }
//     std::cout << "YEdges for Cell 0,0,0" << std::endl;
//     for (auto entity : cell.getYEdges())
//     {
//         std::cout << entity << std::endl;
//     }
//     std::cout << "ZEdges for Cell 0,0,0" << std::endl;
//     for (auto entity : cell.getZEdges())
//     {
//         std::cout << entity << std::endl;
//     }
//     std::cout << "XFace for Cell 0,0,0" << std::endl;
//     for (auto entity : cell.getXFaces())
//     {
//         std::cout << entity << std::endl;
//     }
//     std::cout << "YFaces for Cell 0,0,0" << std::endl;
//     for (auto entity : cell.getYFaces())
//     {
//         std::cout << entity << std::endl;
//     }
//     std::cout << "ZFaces for Cell 0,0,0" << std::endl;
//     for (auto entity : cell.getZFaces())
//     {
//         std::cout << entity << std::endl;
//     }
// }

// TEST(MeshTest, MeshConnectivityTest)
// {
//     Grid grid(3,3,3);

//     Cell cell0(grid, 0,0,0);
//     printCellDetails(cell0);

//     Cell cell1(grid, 1,0,0);
//     printCellDetails(cell1);
// }

// TEST(MeshTest, MeshInterpolation)
// {
//     Grid grid(2,2,2);

//     std::vector<double> u(grid.getSize(), 1.0); // Initialize All ones

//     NodeIndex nodeInd(grid);

//     u[nodeInd(0,0,0)] = 0.0;
//     u[nodeInd(1,0,0)] = 0.0;
//     u[nodeInd(1,1,0)] = 0.0;
//     u[nodeInd(0,1,0)] = 0.0;
//     u[nodeInd(0,0,1)] = 10.0;
//     u[nodeInd(1,0,1)] = 10.0;
//     u[nodeInd(1,1,1)] = 10.0;
//     u[nodeInd(0,1,1)] = 10.0;

//     // Interpolate Positions
//     std::array<double,3> point{0.0, 0.0, 0.0};

//     double sum = 0.0;
//     auto nodes = Cell(grid, 0,0,0).getNodes();   
//     for (int i = 0; i < int(nodes.size()); ++i)
//     {
//         double basis = LegendreBasis3D<double>::eval(i, point[0], point[1], point[2]);
//         sum += basis*u[nodes[i]];
//         std::cout << "Basis " << basis << " " << u[nodes[i]] << " " << nodes[i] << std::endl;
//     }

//     std::cout << sum << std::endl;
// }

// TEST(MeshTest, MassMatrix)
// {
//     Grid grid(2,2,2);

//     auto nodes = Cell(grid, 0,0,0).getNodes();  
//     auto massInt = [&](auto x, auto y, auto z)
//     {
//         Matrix<double, 8> sum(0.0);

//         for (int i = 0; i < int(nodes.size()); ++i)
//         {
//             for (int j = 0; j < int(nodes.size()); ++j)
//             {
//                 double basis_i = LegendreBasis3D<double>::eval(i, x, y, z);
//                 double basis_j = LegendreBasis3D<double>::eval(j, x, y, z);
//                 sum(i,j) = basis_i*basis_j;
//             }
//         }

//         return sum;
//     };


//     Matrix<double,8> result = GaussLegendreQuadrature::integrate3D<5>(massInt, Matrix<double,8>(0.0));

//     std::cout << result << std::endl;


//     // auto nodes = Cell(grid, 0,0,0).getNodes();   
//     // for (int i = 0; i < int(nodes.size()); ++i)
//     // {
//     //     double basis = LegendreBasis3D<double>::eval(i, point[0], point[1], point[2]);
//     //     sum += basis*u[nodes[i]];
//     //     std::cout << "Basis " << basis << " " << u[nodes[i]] << " " << nodes[i] << std::endl;
//     // }
// }
