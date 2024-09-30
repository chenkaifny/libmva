rm -rf bin
rm -rf build
rm -rf lib
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/linux_gcc_x64.cmake ..
make -j8