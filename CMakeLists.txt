# ccmake version
cmake_minimum_required (VERSION 3.2)

# project
project(test)

# output path
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


# package
#find_package(OpenCV REQUIRED)
#if (OpenCV_FOUND)
#  message(STATUS "found submodule OpenCV")
#  message(STATUS ${OpenCV_INCLUDE_DIRS})
#  message(STATUS ${OpenCV_LIBS})
#endif()

# include
#include_directories(${OpenCV_INCLUDE_DIRS})

# execute
#add_executable(test main.cpp)

# sub module
add_subdirectory(src/mva_platform)
add_subdirectory(src/mva_recog)

# depends
#target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS})