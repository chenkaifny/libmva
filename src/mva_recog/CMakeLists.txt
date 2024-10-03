# ccmake version
cmake_minimum_required (VERSION 3.2)

# project
project(mvare)

# compile definition
add_compile_definitions(MVARE_EXPORT)

add_library(mvare 
 mva_feature_match.cc)

 include_directories(mvare PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
 include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include/mva_recog)
 include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)