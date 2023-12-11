cmake_minimum_required(VERSION 3.10)

project(prog)

set(CMAKE_CXX_STANDARD 17)

add_library(complex complex.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(main2
    main.cpp
    complex.cpp)