# ccmake version
cmake_minimum_required (VERSION 3.2)

# project
project(mvap)

# compile definition
add_compile_definitions(MVAP_EXPORT)

add_library(mvap 
 src/mva_mat.cc
 src/mva_kdtree.cc)

 include_directories(mvap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
 include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
 include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)