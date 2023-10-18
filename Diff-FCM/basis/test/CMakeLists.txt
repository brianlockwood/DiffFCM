add_executable(basisTest)
target_sources(basisTest PRIVATE LegendrePolynomialsTest.cpp LegendreBasisTest.cpp BsplineTest.cpp
               BsplineBasisTest.cpp)
target_link_libraries(basisTest PRIVATE basis ${CONAN_LIBS})

gtest_discover_tests(basisTest)
