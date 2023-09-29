cmake_minimum_required(VERSION 3.22)
project(DumbDB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("include")
include_directories("src/memtable")
include_directories("src/storage")
include_directories("src/balanced_tree")
include_directories("src/balanced_tree/red_black_tree")

file(GLOB SOURCES "src/*.cpp" "src/memtable/*.cpp" "src/storage/*.cpp" "src/balanced_tree/*.cpp")

add_library(DumbDB ${SOURCES})

add_subdirectory(test)