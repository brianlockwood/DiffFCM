#include "basis/GaussLegendreQuadratureRule.h"

#include <pybind11/pybind11.h>

#include <iostream>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

// double integrate1D(int N)
// {
//     auto F = [](double x) 
//     { 
//         return std::cos(3.14159*x/2.0);
//     };

//     if (N == 1)
//     {
//         std::cout << "Hello 1" << std::endl;
//         return GaussLegendreQuadrature::integrate1D<1>(F);
//     }
//     if (N == 3)
//     {
//         std::cout << "Hello 3" << std::endl;
//         return GaussLegendreQuadrature::integrate1D<3>(F);
//     }
//     if (N == 5)
//     {
//         std::cout << "Hello 5" << std::endl;
//         return GaussLegendreQuadrature::integrate1D<5>(F);
//     }

//     return 0.0;
// }

// double integrate2D(int N)
// {
//     auto F = [](double x, double y) 
//     { 
//         return std::cos(3.14159*x/2.0)*std::cos(3.14159*y/2.0);
//     };

//     if (N == 1)
//     {
//         std::cout << "Hello 1" << std::endl;
//         return GaussLegendreQuadrature::integrate2D<1>(F);
//     }
//     if (N == 3)
//     {
//         std::cout << "Hello 3" << std::endl;
//         return GaussLegendreQuadrature::integrate2D<3>(F);
//     }
//     if (N == 5)
//     {
//         std::cout << "Hello 5" << std::endl;
//         return GaussLegendreQuadrature::integrate2D<5>(F);
//     }

//     return 0.0;
// }

// double integrate3D(int N)
// {
//     auto F = [](double x, double y, double z) 
//     { 
//         return std::cos(3.14159*x/2.0)*std::cos(3.14159*y/2.0)*std::cos(3.14159*z/2.0);
//     };

//     if (N == 1)
//     {
//         std::cout << "Hello 1" << std::endl;
//         return GaussLegendreQuadrature::integrate3D<1>(F);
//     }
//     if (N == 3)
//     {
//         std::cout << "Hello 3" << std::endl;
//         return GaussLegendreQuadrature::integrate3D<3>(F);
//     }
//     if (N == 5)
//     {
//         std::cout << "Hello 5" << std::endl;
//         return GaussLegendreQuadrature::integrate3D<5>(F);
//     }

//     return 0.0;
// }


// namespace py = pybind11;

// PYBIND11_MODULE(gauss_quadrature_python, m) {
//     m.doc() = R"pbdoc(
//         Gauss Quadrature
//         -----------------------
//         .. currentmodule:: gauss_quadrature
//         .. autosummary::
//            :toctree: _generate
//            integrate1D
//     )pbdoc";

//     m.def("integrate1D", &integrate1D, R"pbdoc(
//         Integrate test function in 1D
//     )pbdoc");

//     m.def("integrate2D", &integrate2D, R"pbdoc(
//         Integrate test function in 2D
//     )pbdoc");

//     m.def("integrate3D", &integrate3D, R"pbdoc(
//         Integrate test function in 3D
//     )pbdoc");

// #ifdef VERSION_INFO
//     m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
// #else
//     m.attr("__version__") = "dev";
// #endif
// }

