cmake_minimum_required(VERSION 3.11)
project(Bigfloat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)


add_library(BigFloat BigFloat.cpp BigFloat.h)

add_executable(PiCalc pi.cpp
        BigFloat
)

add_executable(Tests BigFloat Tests.cpp)
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)