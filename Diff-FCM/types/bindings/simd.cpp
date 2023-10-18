#include "types/simd.h"

#include <pybind11/pybind11.h>

#include <iostream>
#include <iomanip>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

void test()
{
#ifdef SSE2
    v2d v{0.001023, 10102.4059020};

    double xs[2];
    _mm_store_pd(xs, v.data);

    std::cout << std::setprecision(15) << std::endl;
    std::cout << xs[0] << std::endl;
    std::cout << xs[1] << std::endl;
#endif
}



PYBIND11_MODULE(customTypes, m) {
    m.doc() = R"pbdoc(
        TypesTest
        -----------------------
        .. currentmodule:: customTypes
        .. autosummary::
           :toctree: _generate
           eval
    )pbdoc";

    m.def("test", &test, R"pbdoc(
        Run tests for basic types
    )pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
