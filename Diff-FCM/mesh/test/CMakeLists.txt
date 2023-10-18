add_executable(meshTest)
target_sources(meshTest PRIVATE MeshTest.cpp MeshStorageTest.cpp SparseMatrixTest.cpp)
target_link_libraries(meshTest PRIVATE mesh basis ${CONAN_LIBS})

gtest_discover_tests(meshTest)
