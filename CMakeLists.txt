cmake_minimum_required(VERSION 3.26)
#set(CMAKE_OSX_ARCHITECTURES x86_64)
project(Bigfloat)

set(CMAKE_CXX_STANDARD 17)

find_package(Catch2 3 REQUIRED)

add_library(BigFloat BigFloat.cpp BigFloat.h)

add_executable(PiCalc pi.cpp
        BigFloat
)

add_executable(Tests BigFloat Tests.cpp)
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)
