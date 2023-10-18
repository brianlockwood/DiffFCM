find_package(pybind11 CONFIG)

pybind11_add_module(customTypes simd.cpp)
target_link_libraries(customTypes PRIVATE types)