add_executable(typesTest)
target_sources(typesTest PRIVATE VectorTest.cpp MatrixTest.cpp)
target_link_libraries(typesTest PRIVATE types ${CONAN_LIBS})

gtest_discover_tests(typesTest)
