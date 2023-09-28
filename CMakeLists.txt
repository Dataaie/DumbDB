cmake_minimum_required(VERSION 3.22)
project(DumbDB)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(DumbDB STATIC src/dumb.cpp)

target_include_directories(DumbDB PUBLIC include/)

add_subdirectory(test)