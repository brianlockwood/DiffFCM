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

// #ifdef SSE2
// #include <xmmintrin.h>
// #endif

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

template <int Order>
std::vector<double> bSplineFit(const std::vector<double> &x, std::function<double(double)> function)
{
    int N = x.size();

    constexpr int IntegrationRule = 2*Order + 1;

    constexpr int BSize = BSpline<Order, double>::size();
    int dofTotal = Order == 0 ? N-1 : N + (BSize-2)*(N-1);

    std::vector<double> b(dofTotal, 0.0);
    SparseMatrix A(dofTotal);

    BSpline<Order, double> bSpline;

    for (int i = 0; i < N-1; ++i)
    {
        auto integrand = [&](double w, double xp)
        {
            double xs = x[i] + (x[i+1]-x[i])*(xp + 1.0)/2.0;

            for (int k = 0; k < BSize; ++k)
            {
                int globalDof = i*(BSize-1) + k;
                b[globalDof] += w*bSpline(k, xp)*function(xs)/2;

                for (int l = 0; l < BSize; ++l)
                {
                    int globalDof2 = i*(BSize-1) + l;
                    A(globalDof, globalDof2) += w*bSpline(k, xp)*bSpline(l, xp)/2;
                }
            }
        };

        GaussLegendreQuadrature::gaussSum<IntegrationRule>(integrand);
    }

    A.assemble();

    return ::solve(A, b);
}

template <int Order>
void interpolate(int n, double dx, const std::vector<double> &x, double *xPresentation, double *u, const std::vector<double> &sol)
{
    constexpr int BSize = BSpline<Order, double>::size();
    BSpline<Order, double> bSpline;

    for (int idx = 0; idx < n; idx++)
    {
        double xs = xPresentation[idx];

        int i = (xs-x[0])/dx;

        double sum = 0.0;
        for (int k = 0; k < BSize; ++k)
        {
            int globalDof = i*(BSize-1) + k;

            double xp = 2*(xs - x[i])/dx - 1;

            sum += bSpline(k, xp)*sol[globalDof];
        }

        u[idx] = sum;
    }
}

pybind11::array_t<double> fit1D(int N, int p, pybind11::array_t<double> xPresentation, 
                               std::function<double(double)> function)
{
    if (p > 4)
        throw std::runtime_error("Unsupport Polynomial Order");

    double Xmin = std::numeric_limits<double>::max();
    double Xmax = -std::numeric_limits<double>::max();

    pybind11::buffer_info buf1 = xPresentation.request();
    double *ptr1 = static_cast<double *>(buf1.ptr);
    for (int i = 0; i < buf1.shape[0]; ++i)
    {
        Xmin = std::min(Xmin, ptr1[i]);
        Xmax = std::max(Xmax, ptr1[i]);
    }

    std::cout << Xmin << " " << Xmax << std::endl;

    double L = (Xmax - Xmin);

    std::vector<double> x(N, 0.0);

    double dx = L/(1.0*(N-1));

    for (int i = 0; i < N; ++i)
    {
        x[i] = Xmin + dx*i;
    }

    std::vector<double> sol;
    switch(p)
    {
        case 1:
            sol = bSplineFit<1>(x, function);
            break;
        case 2:
            sol = bSplineFit<2>(x, function);
            break;
        case 3:
            sol = bSplineFit<3>(x, function);
            break;
        case 4:
            sol = bSplineFit<4>(x, function);
            break;
    };

    auto result = pybind11::array_t<double>(buf1.size);

    pybind11::buffer_info buf3 = result.request();

    double *ptr3 = static_cast<double *>(buf3.ptr);

    switch(p)
    {
        case 1:
            interpolate<1>(buf1.shape[0], dx, x, ptr1, ptr3, sol);
            break;
        case 2:
            interpolate<2>(buf1.shape[0], dx, x, ptr1, ptr3, sol);
            break;
        case 3:
            interpolate<3>(buf1.shape[0], dx, x, ptr1, ptr3, sol);
            break;
        case 4:
            interpolate<4>(buf1.shape[0], dx, x, ptr1, ptr3, sol);     
            break;
    }

    return result;
}

void init_fit1D(py::module_ &m)
{
    m.def("fit1D", &fit1D, R"pbdoc(
        Test fitting of a function using BSplines
    )pbdoc", py::arg("N"), py::arg("P"), py::arg("X"), py::arg("Function"));
}

