cmake_minimum_required(VERSION 3.26)
project(Bigfloat)

set(CMAKE_CXX_STANDARD 17)

add_executable(Bigfloat main.cpp
        BigFloat.cpp
        BigFloat.h
        pi.cpp)
