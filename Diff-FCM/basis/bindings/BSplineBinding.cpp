#include "basis/Bspline.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <cassert>

#include <iostream>
#include <chrono>

// #ifdef SSE2
// #include <xmmintrin.h>
// #endif

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

double eval(int N, int index, double x)
{
    switch (N)
    {
        case 0:
        {
            return BSpline<0, double>()(index, x);
        }
        case 1:
        {
            return BSpline<1, double>()(index, x);
        }
        case 2:
        {
            return BSpline<2, double>()(index, x);
        }
        case 3:
        {
            return BSpline<3, double>()(index, x);
        }
        case 4:
        {
            return BSpline<4,double>()(index, x);
        }
        case 5:
        {
            return BSpline<5,double>()(index, x);
        }
        case 6:
        {
            return BSpline<6,double>()(index, x);
        }
        case 7:
        {
            return BSpline<7,double>()(index, x);
        }
        case 8:
        {
            return BSpline<8,double>()(index, x);
        }
        case 9:
        {
            return BSpline<9,double>()(index, x);
        }
        default:
            assert(false && "LegendrePolynomial: Order not implemented");
    }

    return 0;
}


namespace py = pybind11;

PYBIND11_MODULE(bspline_python, m) {
    m.doc() = R"pbdoc(
        BSpline
        -----------------------
        .. currentmodule:: basis
        .. autosummary::
           :toctree: _generate
           eval
    )pbdoc";

    m.def("eval", &eval, R"pbdoc(
        Evaluate BSpline of Order N with index i for Point x
    )pbdoc", py::arg("N"), py::arg("Index"), py::arg("x"));

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
