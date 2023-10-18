#include "basis/LegendreBasis.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <cassert>

#include <iostream>
#include <chrono>

#ifdef SSE2
#include <xmmintrin.h>
#endif

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

double eval1D(int N, double x)
{
    switch (N)
    {
        case 0:
            return LegendreBasis1D<double>::eval<0>(x);
        case 1:
            return LegendreBasis1D<double>::eval<1>(x);
        case 2:
            return LegendreBasis1D<double>::eval<2>(x);
        case 3:
            return LegendreBasis1D<double>::eval<3>(x);
        case 4:
            return LegendreBasis1D<double>::eval<4>(x);
        case 5:
            return LegendreBasis1D<double>::eval<5>(x);
        case 6:
            return LegendreBasis1D<double>::eval<6>(x);
        case 7:
            return LegendreBasis1D<double>::eval<7>(x);
        case 8:
            return LegendreBasis1D<double>::eval<8>(x);
        case 9:
            return LegendreBasis1D<double>::eval<9>(x);
        default:
            assert(false && "LegendrePolynomial: Order not implemented");
    }

    return 0;
}


double eval2D(int N, double x, double y)
{
    switch (N)
    {
        case 0:
            return LegendreBasis2D<double>::eval<0>(x, y);
        case 1:
            return LegendreBasis2D<double>::eval<1>(x, y);
        case 2:
            return LegendreBasis2D<double>::eval<2>(x, y);
        case 3:
            return LegendreBasis2D<double>::eval<3>(x, y);
        case 4:
            return LegendreBasis2D<double>::eval<4>(x, y);
        case 5:
            return LegendreBasis2D<double>::eval<5>(x, y);
        case 6:
            return LegendreBasis2D<double>::eval<6>(x, y);
        case 7:
            return LegendreBasis2D<double>::eval<7>(x, y);
        case 8:
            return LegendreBasis2D<double>::eval<8>(x, y);
        default:
            assert(false && "LegendrePolynomial: Order not implemented");
    }

    return 0;
}


double eval3D(int N, double x, double y, double z)
{
    switch (N)
    {
        case 0:
            return LegendreBasis3D<double>::eval<0>(x, y, z);
        case 1:
            return LegendreBasis3D<double>::eval<1>(x, y, z);
        case 2:
            return LegendreBasis3D<double>::eval<2>(x, y, z);
        case 3:
            return LegendreBasis3D<double>::eval<3>(x, y, z);
        case 4:
            return LegendreBasis3D<double>::eval<4>(x, y, z);
        case 5:
            return LegendreBasis3D<double>::eval<5>(x, y, z);
        case 6:
            return LegendreBasis3D<double>::eval<6>(x, y, z);
        case 7:
            return LegendreBasis3D<double>::eval<7>(x, y, z);
        default:
            assert(false && "LegendrePolynomial: Order not implemented");
    }

    return 0;
}


namespace py = pybind11;

PYBIND11_MODULE(basis_python, m) {
    m.doc() = R"pbdoc(
        LegendreBasis
        -----------------------
        .. currentmodule:: basis
        .. autosummary::
           :toctree: _generate
           eval
    )pbdoc";

    m.def("eval1D", &eval1D, R"pbdoc(
        Evaluate LegendrePolynomial of Order N for Point x
    )pbdoc", py::arg("N"), py::arg("x"));

    m.def("eval2D", &eval2D, R"pbdoc(
        Evaluate LegendrePolynomial of Order N for Point x
    )pbdoc", py::arg("N"), py::arg("x"), py::arg("y"));

    m.def("eval3D", &eval3D, R"pbdoc(
        Evaluate LegendrePolynomial of Order N for Point x
    )pbdoc", py::arg("N"), py::arg("x"), py::arg("y"), py::arg("z"));

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
