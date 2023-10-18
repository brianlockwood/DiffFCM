add_library(types INTERFACE)
target_sources(types INTERFACE types/simd.h types/Matrix.h types/Vector.h)
target_include_directories(types INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
