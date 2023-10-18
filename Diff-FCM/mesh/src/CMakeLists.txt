add_library(mesh)
target_sources(mesh PRIVATE mesh/Coord.h mesh/Grid.h 
                            mesh/Grid.cpp mesh/NodeIndex.h 
                            mesh/EdgeIndex.h mesh/FaceIndex.h
                            mesh/CellIndex.h mesh/Cell.h
                            mesh/DOF.h)
target_include_directories(mesh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mesh PRIVATE types)
