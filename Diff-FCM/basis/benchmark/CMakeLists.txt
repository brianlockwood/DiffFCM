add_executable(basisBenchmark)
target_sources(basisBenchmark PRIVATE BsplineBench.cpp LegendrePolynomialsBench.cpp LegendreBasisBench.cpp GaussLegendreIntegrateBench.cpp)
target_link_libraries(basisBenchmark PRIVATE basis ${CONAN_LIBS})

