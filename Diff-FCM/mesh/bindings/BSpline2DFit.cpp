#include "basis/Bspline.h"
#include "basis/GaussLegendreQuadratureRule.h"
#include "mesh/SparseMatrix.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/functional.h>

#include <cassert>

#include <iostream>
#include <chrono>
#include <stdexcept>

#include "mesh/Grid.h"
#include "mesh/DOF.h"
#include "mesh/Coord.h"

// #ifdef SSE2
// #include <xmmintrin.h>
// #endif

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

template <int Order>
std::vector<double> bSplineFit(const Grid<2> &grid, 
                               const GridDofs &gridDof,
                               std::function<double(double, double)> function)
{
    constexpr int IntegrationRule = 2*Order + 1;

    int dofTotal = gridDof.totalDofs;

    std::vector<double> b(dofTotal, 0.0);
    SparseMatrix A(dofTotal);

    Coord<2> nodeCoords(grid);

    GridLoops::cellLoop(grid, [&](int i, int j)
    {
        auto xI = nodeCoords(i,j);
        auto xP  = nodeCoords(i+1,j+1);

        auto cellDofs = gridDof.cellDofs(i,j);

        double dx = nodeCoords._delta[0];
        double dy = nodeCoords._delta[1];

        BSplineBasis<Order, double> basisFunctions;

        auto integrand = [&](double w, double xp, double yp)
        {
            double xs = xI[0] + (xP[0]-xI[0])*(xp + 1.0)/2.0;
            double ys = xI[1] + (xP[1]-xI[1])*(yp + 1.0)/2.0;

            for (auto basis : basisFunctions)
            {
                int globalDof = cellDofs[basis.index()];

                b[globalDof] += w*basis.eval(xp, yp)*function(xs,ys)*dx*dy/4;
                for (auto basis2 : basisFunctions)
                {
                    int globalDof2 = cellDofs[basis2.index()];
                    A(globalDof, globalDof2) += w*basis.eval(xp, yp)*basis2.eval(xp, yp)*dx*dy/4;
                }
            }
        };

        GaussLegendreQuadrature::gaussSum2D<IntegrationRule>(integrand);
    });

    A.assemble();

    return ::solve(A, b);
}

template <int Order>
void interpolate(const Grid<2> &grid, 
                 const GridDofs &gridDof,
                 pybind11::array_t<double> xPresentation, 
                 pybind11::array_t<double> yPresentation,
                 pybind11::array_t<double> u, 
                 const std::vector<double> &sol)
{
    BSpline<Order, double> bSpline;

    Coord<2> nodeCoords(grid);

    auto r = xPresentation.unchecked<2>();
    auto s = yPresentation.unchecked<2>();
    auto t = u.mutable_unchecked<2>();

    for (py::ssize_t ip = 0; ip < r.shape(0); ip++)
    {
        for (py::ssize_t jp = 0; jp < r.shape(1); jp++)
        {
            double xs = r(ip,jp);
            double ys = s(ip,jp);

            auto [i,j] = nodeCoords.getNode({xs, ys});

            auto cellDofs = gridDof.cellDofs(i,j);

            BSplineBasis<Order, double> basisFunctions;

            double sum = 0.0;
            for (auto basis : basisFunctions)
            {
                int globalDof = cellDofs[basis.index()];

                auto [xp, yp] = nodeCoords.getLocalCoord(i,j, {xs, ys});    

                sum += basis.eval(xp, yp)*sol[globalDof];
            }

            t(ip,jp) = sum;
        }
    }
}

pybind11::array_t<double> fit2D(int N, int M, int p, 
                                pybind11::array_t<double> xPresentation, 
                                pybind11::array_t<double> yPresentation,
                                std::function<double(double, double)> function)
{
    if (p > 4)
        throw std::runtime_error("Unsupport Polynomial Order");

    double Xmin = std::numeric_limits<double>::max();
    double Xmax = -std::numeric_limits<double>::max();

    double Ymin = std::numeric_limits<double>::max();
    double Ymax = -std::numeric_limits<double>::max();

    auto r = xPresentation.unchecked<2>();
    auto s = yPresentation.unchecked<2>();
    for (py::ssize_t i = 0; i < r.shape(0); i++)
    {
        for (py::ssize_t j = 0; j < r.shape(1); j++)
        {
            Xmin = std::min(Xmin, r(i,j));
            Xmax = std::max(Xmax, r(i,j));
            Ymin = std::min(Ymin, s(i,j));
            Ymax = std::max(Ymax, s(i,j));
        }
    }

    Grid<2> grid(N, M);

    grid.setBounds({Xmin, Ymin}, {Xmax, Ymax});

    GridStorage<2, int> cellOrder(N-1,M-1);
    cellOrder = p+1;

    GridDofs gridDof = labelDegreesOfFreedom(grid, cellOrder);

    std::vector<double> sol;
    switch(p)
    {
        case 1:
            sol = bSplineFit<1>(grid, gridDof, function);
            break;
        case 2:
            sol = bSplineFit<2>(grid, gridDof, function);
            break;
        case 3:
            sol = bSplineFit<3>(grid, gridDof, function);
            break;
        case 4:
            sol = bSplineFit<4>(grid, gridDof, function);
            break;
    };

    auto result = py::array(py::buffer_info(
        nullptr,            /* Pointer to data (nullptr -> ask NumPy to allocate!) */
        sizeof(double),     /* Size of one item */
        py::format_descriptor<double>::value, /* Buffer format */
        r.ndim(),          /* How many dimensions? */
        { r.shape(0), r.shape(1) },  /* Number of elements for each dimension */
        { r.shape(1)*sizeof(double), sizeof(double) }  /* Strides for each dimension */
    ));

    switch(p)
    {
        case 1:
            interpolate<1>(grid, gridDof, xPresentation, yPresentation, result, sol);
            break;
        case 2:
            interpolate<2>(grid, gridDof, xPresentation, yPresentation, result, sol);
            break;
        case 3:
            interpolate<3>(grid, gridDof, xPresentation, yPresentation, result, sol);
            break;
        case 4:
            interpolate<4>(grid, gridDof, xPresentation, yPresentation, result, sol);
            break;
    }

    return result;
}

void init_fit2D(py::module_ &m)
{
    m.def("fit2D", &fit2D, R"pbdoc(
        Test fitting of a function using BSplines
    )pbdoc", py::arg("N"), py::arg("M"), py::arg("P"), py::arg("X"), py::arg("Y"), py::arg("Function"));
}

