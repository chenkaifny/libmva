# set system name
set(CMAKE_SYSTEM_NAME Linux)

# set object platform
set(CMAKE_SYSTEM_PROCESSOR "x86-64")

# set cross-compile-toolchain root path
set(CROSS_CHAIN_PATH /usr/bin)

# set c compiler
set(CMAKE_C_COMPILER "${CROSS_CHAIN_PATH}/gcc")

# set cpp compiler
set(CMAKE_CXX_COMPILER "${CROSS_CHAIN_PATH}/g++")

# set lib ar
set(CMAKE_AR "${CROSS_CHAIN_PATH}/gcc-ar")

# set build type
set(CMAKE_BUILD_TYPE "Release")