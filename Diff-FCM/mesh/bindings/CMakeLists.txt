find_package(pybind11 CONFIG)

pybind11_add_module(mesh_python MeshPython.cpp BSpline1DFit.cpp BSpline2DFit.cpp)
target_link_libraries(mesh_python PRIVATE basis mesh)
