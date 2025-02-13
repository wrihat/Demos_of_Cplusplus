cmake_minimum_required(VERSION 3.22)
project(heap_usage)
set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(heap heap.cpp)

