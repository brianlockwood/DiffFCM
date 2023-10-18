
cmake_minimum_required(VERSION 3.4...3.18)
project(FCMProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-O0 -g -Wall -Wextra -pedantic -Werror)
else()
    add_compile_options(-O3 -Wall -Wextra -pedantic -Werror)
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(extern/pybind11)

set(SIMD_INSTRUCTIONS SSE2 CACHE STRING "Specify SIMD Instruction Set")
set_property(CACHE SIMD_INSTRUCTIONS PROPERTY STRINGS SSE2 AVX NONE)

if (SIMD_INSTRUCTIONS STREQUAL "SSE2")
    add_definitions(-DSSE2)
elseif (SIMD_INSTRUCTIONS STREQUAL "AVX")
    add_definitions(-DAVX)
    add_compile_options(-mavx)
endif()

enable_testing()

include(GoogleTest)

include_directories(${CMAKE_SOURCE_DIR}/Diff-FCM)
add_subdirectory(Diff-FCM)
