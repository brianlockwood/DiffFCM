#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/functional.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

void init_fit1D(py::module_ &);
void init_fit2D(py::module_ &);

PYBIND11_MODULE(mesh_python, m) {
    m.doc() = R"pbdoc(
        Mesh
        -----------------------
        .. currentmodule:: mesh_python
        .. autosummary::
           :toctree: _generate
           fit1D
           fit2D
    )pbdoc";

    init_fit1D(m);
    init_fit2D(m);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}