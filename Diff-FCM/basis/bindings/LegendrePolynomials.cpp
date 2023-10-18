#include "basis/LegendrePolynomials.h"

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


double eval(int N, double x)
{
    switch (N)
    {
        case 0:
            return LegendrePolynomial<0, double>::eval(x);
        case 1:
            return LegendrePolynomial<1, double>::eval(x);
        case 2:
            return LegendrePolynomial<2, double>::eval(x);
        case 3:
            return LegendrePolynomial<3, double>::eval(x);
        case 4:
            return LegendrePolynomial<4, double>::eval(x);
        case 5:
            return LegendrePolynomial<5, double>::eval(x);
        case 6:
            return LegendrePolynomial<6, double>::eval(x);
        case 7:
            return LegendrePolynomial<7, double>::eval(x);
        case 8:
            return LegendrePolynomial<8, double>::eval(x);
        case 9:
            return LegendrePolynomial<9, double>::eval(x);
        default:
            assert(false && "LegendrePolynomial: Order not implemented");
    }

    return 0;
}

template <int N>
void evalVector_impl(double *y_ptr, int size, double *x_ptr)
{
#ifdef SSE2
    for (int i = 0; i < size; i += 2)
    {
        __m128d f = _mm_loadu_pd(&x_ptr[i]);

        v2d result = LegendrePolynomial<N, v2d>::eval(v2d(f));
        _mm_store_pd(&y_ptr[i], result.data);
    }
#elif AVX
    std::cout << "Hello" << std::endl;
    for (int i = 0; i < size; i += 4)
    {
        __m256d f = _mm256_loadu_pd(&x_ptr[i]);

        v4d result = LegendrePolynomial<N, v4d>::eval(v4d(f));
        _mm256_store_pd(&y_ptr[i], result.data);
    }
#else
    for (int i = 0; i < size; ++i)
    {
        y_ptr[i] = LegendrePolynomial<N, double>::eval(x_ptr[i]);
    }
#endif
}

pybind11::array_t<double> evalVector(int N, pybind11::array_t<double> &x)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();

    pybind11::buffer_info x_info = x.request();

    auto result = pybind11::array_t<double>(x_info.size);

    pybind11::buffer_info y_info = result.request();

    double *x_ptr = static_cast<double *>(x_info.ptr);
    double *y_ptr = static_cast<double *>(y_info.ptr);

    int size = x_info.shape[0];

    switch (N)
    {
        case 0:
            evalVector_impl<0>(y_ptr, size, x_ptr);
            break;
        case 1:
            evalVector_impl<1>(y_ptr, size, x_ptr);
            break;
        case 2:
            evalVector_impl<2>(y_ptr, size, x_ptr);
            break;
        case 3:
            evalVector_impl<3>(y_ptr, size, x_ptr);
            break;
        case 4:
            evalVector_impl<4>(y_ptr, size, x_ptr);
            break;
        case 5:
            evalVector_impl<5>(y_ptr, size, x_ptr);
            break;
        case 6:
            evalVector_impl<6>(y_ptr, size, x_ptr);
            break;
        case 7:
            evalVector_impl<7>(y_ptr, size, x_ptr);
            break;
        case 8:
            evalVector_impl<8>(y_ptr, size, x_ptr);
            break;
        case 9:
            evalVector_impl<9>(y_ptr, size, x_ptr);
            break;
        default:
            assert(false && "evalVector: Order not implemented");
    }

    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << "Filled in " << ms_double.count() << "ms\n";

    return result;
}

namespace py = pybind11;

PYBIND11_MODULE(legendre_python, m) {
    m.doc() = R"pbdoc(
        LegendrePolynomails
        -----------------------
        .. currentmodule:: legendre
        .. autosummary::
           :toctree: _generate
           eval
    )pbdoc";

    m.def("eval", &eval, R"pbdoc(
        Evaluate LegendrePolynomial of Order N for Point x
    )pbdoc", py::arg("N"), py::arg("x"));

    m.def("evalVector", &evalVector, R"pbdoc(
        Evaluate LegendrePolynomial of Order N for all Points in x
    )pbdoc", py::arg("N"), py::arg("x"));

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
