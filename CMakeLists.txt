cmake_minimum_required(VERSION 3.22)
project(DumbDB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("include")
include_directories("memtable/include")
include_directories("storage/include")
include_directories("balanced_tree/include")
include_directories("balanced_tree/red_black_tree/include")

file(GLOB SOURCES "src/*.cpp" "memtable/src/*.cpp" "storage/src/*.cpp" "balanced_tree/src/*.cpp" "balanced_tree/red_black_tree/src/*.cpp")

add_library(DumbDB ${SOURCES})

add_subdirectory(test)