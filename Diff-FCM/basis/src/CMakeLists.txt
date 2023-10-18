add_library(basis INTERFACE)
target_sources(basis INTERFACE basis/LegendrePolynomials.h 
                               basis/LegendreBasis.h
                               basis/GaussLegendreQuadratureRule.h
                               basis/Bspline.h)
target_include_directories(basis INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(basis INTERFACE types)
