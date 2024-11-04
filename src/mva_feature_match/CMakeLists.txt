# ccmake version
cmake_minimum_required (VERSION 3.2)

# project
project(mvafeaturematch)

# compile definition
add_compile_definitions(MVARE_EXPORT)

add_library(mvafeaturematch 
 mva_feature_match.cc)

 include_directories(mvare PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
 include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include/mva_feature_match)
 include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)